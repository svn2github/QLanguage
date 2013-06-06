﻿/********************************************************************
	created:	2013/06/01
	created:	1:6:2013   20:08
	filename: 	\QLanguage\Parser\SyntaxTree\SyntaxTree_Value.cpp
	file path:	\QLanguage\Parser\SyntaxTree
	file base:	SyntaxTree_Value
	file ext:	cpp
	author:		lwch
	
	purpose:	
*********************************************************************/
#include "../Parser.h"
#include "SyntaxTree_Value.h"

namespace QLanguage
{
    SyntaxTree_Value::SyntaxTree_Value(const string& value, Type type) : parent(sizeof(SyntaxTree_Value)), value(value), type(type)
    {
    }

    SyntaxTree_Value::~SyntaxTree_Value()
    {
    }

    void SyntaxTree_Value::print(ostream& stream, uint indent)const
    {
    }

    // value_desc -> "true"
    // value_desc -> "false"
    // value_desc -> "{Real}"
    // value_desc -> "{Digit}"
    // value_desc -> "{String}"
    bool Parser::reduceValueNormal(ushort i)
    {
        SyntaxTree_Value* pValue = allocator<SyntaxTree_Value>::allocate();
        switch (i)
        {
        case VALUE_DESC_TRUE:   // value_desc -> "true"
        case VALUE_DESC_FALSE:  // value_desc -> "false"
            construct(pValue, shifts.top(), SyntaxTree_Value::Boolean);
            break;
        case VALUE_DESC_REAL:   // value_desc -> "{Real}"
            construct(pValue, shifts.top(), SyntaxTree_Value::Real);
            break;
        case VALUE_DESC_DIGIT:  // value_desc -> "{Digit}"
            construct(pValue, shifts.top(), SyntaxTree_Value::Digit);
            break;
        case VALUE_DESC_STRING: // value_desc -> "{String}"
            construct(pValue, shifts.top(), SyntaxTree_Value::String);
            break;
        }

        context.data.insert(pValue);

        syntaxTreeStack.push(pValue);

        shifts.pop();

        return true;
    }
}