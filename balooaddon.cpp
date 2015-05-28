#include <node.h>
#include <node_object_wrap.h>

#include "query.h"

using namespace v8;

void init(Handle<Object> exports)
{
    Query::Init(exports);
}

NODE_MODULE(addon, init)

