﻿/********************************************************************
	created:	2013/06/06
	created:	6:6:2013   16:41
	filename: 	\QLanguage\Parser\SyntaxTree\SyntaxTree_FunctionDeclare.cpp
	file path:	\QLanguage\Parser\SyntaxTree
	file base:	SyntaxTree_FunctionDeclare
	file ext:	cpp
	author:		lwch
	
	purpose:	
*********************************************************************/
#include "../Parser.h"

#include "SyntaxTree_ParamterList.h"
#include "SyntaxTree_FunctionDeclare.h"

namespace QLanguage
{
    SyntaxTree_Function_Declare::SyntaxTree_Function_Declare(const string& name, SyntaxTree_Type& returnType)
        : parent(sizeof(SyntaxTree_Function_Declare))
        , name(name)
        , returnType(returnType)
    {
    }

    SyntaxTree_Function_Declare::SyntaxTree_Function_Declare(const string& name, SyntaxTree_Type& returnType, SyntaxTree_ParamterList* pParamterList)
        : parent(sizeof(SyntaxTree_Function_Declare))
        , name(name)
        , returnType(returnType)
        , pParamterList(pParamterList)
    {
    }

    SyntaxTree_Function_Declare::~SyntaxTree_Function_Declare()
    {
    }

    void SyntaxTree_Function_Declare::print(ostream& stream, uint indent)const
    {
    }

    // function_desc -> type_desc "{Letter}" "(" paramter_list ")" ";"
    bool Parser::reduceFunctionDeclare2()
    {
        shifts.pop();
        shifts.pop();
        shifts.pop();

        SyntaxTree_Function_Declare* pFunctionDeclare = allocator<SyntaxTree_Function_Declare>::allocate();
        construct(pFunctionDeclare, shifts.top(), dynamic_cast<SyntaxTree_Type&>(*syntaxTreeStack[1]), dynamic_cast<SyntaxTree_ParamterList*>(syntaxTreeStack.top()));

        context.data.insert(pFunctionDeclare);

        syntaxTreeStack.pop();
        syntaxTreeStack.pop();
        syntaxTreeStack.push(pFunctionDeclare);

        shifts.pop();
        return true;
    }

    // function_desc -> type_desc "{Letter}" "(" ")" ";"
    bool Parser::reduceFunctionDeclare4()
    {
        shifts.pop();
        shifts.pop();
        shifts.pop();

        SyntaxTree_Function_Declare* pFunctionDeclare = allocator<SyntaxTree_Function_Declare>::allocate();
        construct(pFunctionDeclare, shifts.top(), dynamic_cast<SyntaxTree_Type&>(*syntaxTreeStack.top()));

        context.data.insert(pFunctionDeclare);

        syntaxTreeStack.pop();
        syntaxTreeStack.push(pFunctionDeclare);

        shifts.pop();
        return true;
    }

    // function_desc -> "void" "{Letter}" "(" paramter_list ")" ";"
    bool Parser::reduceFunctionDeclare6()
    {
        shifts.pop();
        shifts.pop();
        shifts.pop();

        SyntaxTree_Type* pReturnType = allocator<SyntaxTree_Type>::allocate();
        construct(pReturnType, "void", SyntaxTree_Type::Void);

        context.data.insert(pReturnType);

        SyntaxTree_Function_Declare* pFunctionDeclare = allocator<SyntaxTree_Function_Declare>::allocate();
        construct(pFunctionDeclare, shifts.top(), *pReturnType);

        context.data.insert(pFunctionDeclare);

        syntaxTreeStack.pop();
        syntaxTreeStack.push(pFunctionDeclare);

        shifts.pop();
        shifts.pop();
        return true;
    }

    // function_desc -> "void" "{Letter}" "(" ")" ";"
    bool Parser::reduceFunctionDeclare8()
    {
        shifts.pop();
        shifts.pop();
        shifts.pop();

        SyntaxTree_Type* pReturnType = allocator<SyntaxTree_Type>::allocate();
        construct(pReturnType, "void", SyntaxTree_Type::Void);

        context.data.insert(pReturnType);

        SyntaxTree_Function_Declare* pFunctionDeclare = allocator<SyntaxTree_Function_Declare>::allocate();
        construct(pFunctionDeclare, shifts.top(), *pReturnType, dynamic_cast<SyntaxTree_ParamterList*>(syntaxTreeStack.top()));

        context.data.insert(pFunctionDeclare);

        syntaxTreeStack.push(pFunctionDeclare);

        shifts.pop();
        shifts.pop();
        return true;
    }
}