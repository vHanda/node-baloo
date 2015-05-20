#include <node.h>
#include <node_object_wrap.h>

#include <Baloo/Query>
#include <Baloo/ResultIterator>

using namespace v8;

void method(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Baloo::Query query;
    query.setSearchString("ink");

    Baloo::ResultIterator it = query.exec();
    QString val("Not Found");
    if (it.next()) {
        val = it.filePath();
    }

    QByteArray arr = val.toUtf8();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, arr.constData()));
}

void init(Handle<Object> exports)
{
    NODE_SET_METHOD(exports, "hello", method);
}

NODE_MODULE(addon, init)

