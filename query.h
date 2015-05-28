#ifndef BALOO_QUERY_NODEJS_H
#define BALOO_QUERY_NODEJS_H

#include <node.h>
#include <node_object_wrap.h>

#include <Baloo/Query>
#include <Baloo/ResultIterator>

// FIXME: Add the following properties
//        * searchString
//        * limit
//
class Query : public node::ObjectWrap
{
public:
    static void Init(v8::Handle<v8::Object> exports);

private:
    Query(const QString& queryString);
    ~Query();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void exec(const v8::FunctionCallbackInfo<v8::Value>& args);

    static v8::Persistent<v8::Function> s_constructor;

    Baloo::Query m_query;
};

#endif
