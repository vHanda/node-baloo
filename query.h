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
