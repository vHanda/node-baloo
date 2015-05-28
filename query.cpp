#include "query.h"

#include <QDebug>
#include <QByteArray>

using namespace v8;

Persistent<Function> Query::s_constructor;

Query::Query(const QString& queryString)
{
    m_query.setSearchString(queryString);
}

Query::~Query()
{
}

void Query::Init(Handle<Object> exports)
{
    Isolate* isolate = Isolate::GetCurrent();

    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "Query"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "exec", exec);

    s_constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "Query"), tpl->GetFunction());
}

// static
void Query::New(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    if (args.IsConstructCall()) {
        if (args.Length() > 1) {
            // Throw exception
            return;
        }

        if (!args[0]->IsUndefined()) {
            if (!args[0]->IsString()) {
                // Throw an exception
                return;
            }

            Local<String> str = args[0]->ToString();
            QByteArray arr;
            arr.resize(str->Utf8Length());
            str->WriteUtf8(arr.data(), arr.length());

            QString queryString = QString::fromUtf8(arr);
            Query* query = new Query(queryString);
            query->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        }
    }
    else {
        // Invoked as plain function, turn into construct call.
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        Local<Function> cons = Local<Function>::New(isolate, s_constructor);
        args.GetReturnValue().Set(cons->NewInstance(argc, argv));
    }
}

void Query::exec(const FunctionCallbackInfo<Value>& args)
{
    if (args.Length() != 0) {
        // Throw an exception!
        return;
    }

    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Query* query = ObjectWrap::Unwrap<Query>(args.Holder());
    Baloo::Query q = query->m_query;
    Baloo::ResultIterator it = q.exec();

    QStringList results;
    while (it.next()) {
        results << it.filePath();
        qDebug() << it.filePath();
    }

    Handle<Array> array = Array::New(isolate, results.size());
    for (int i = 0; i < results.length(); i++) {
        const QByteArray arr = results[i].toUtf8();
        Local<String> str = String::NewFromUtf8(isolate, arr.constData());
        array->Set(i, str);
    }

    args.GetReturnValue().Set(array);
}
