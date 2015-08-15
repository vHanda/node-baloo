/*
 * Copyright (C) 2015  Vishesh Handa <vhanda@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "query.h"

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
            // throw v8::Exception::SyntaxError(v8::String::New("..."));

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
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    if (args.Length() != 1) {
        v8::Local<v8::String> str = v8::String::NewFromUtf8(isolate, "Baloo.Query.exec expects 1 agument");
        isolate->ThrowException(v8::Exception::TypeError(str));
        return;
    }

    if (!args[0]->IsFunction()) {
        v8::Local<v8::String> str = v8::String::NewFromUtf8(isolate, "Argument must be a callback function");
        isolate->ThrowException(v8::Exception::TypeError(str));
        return;
    }

    Query* query = ObjectWrap::Unwrap<Query>(args.Holder());
    Baloo::Query q = query->m_query;
    Baloo::ResultIterator it = q.exec();

    QStringList results;
    while (it.next()) {
        results << it.filePath();
    }

    Handle<Array> array = Array::New(isolate, results.size());
    for (int i = 0; i < results.length(); i++) {
        const QByteArray arr = results[i].toUtf8();
        Local<String> str = String::NewFromUtf8(isolate, arr.constData());
        array->Set(i, str);
    }

    Local<Function> cb = Local<Function>::Cast(args[0]);
    Local<Value> argv[1] = { array };
    cb->Call(isolate->GetCurrentContext()->Global(), 1, argv);
}

