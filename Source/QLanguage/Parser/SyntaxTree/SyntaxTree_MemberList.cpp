﻿/********************************************************************
	created:	2013/06/03
	created:	3:6:2013   11:19
	filename: 	\QLanguage\Parser\SyntaxTree\SyntaxTree_MemberList.cpp
	file path:	\QLanguage\Parser\SyntaxTree
	file base:	SyntaxTree_MemberList
	file ext:	cpp
	author:		lwch
	
	purpose:	
*********************************************************************/
#include "../Parser.h"
#include "SyntaxTree_Name.h"
#include "SyntaxTree_MemberList.h"

namespace QLanguage
{
    SyntaxTree_MemberList::SyntaxTree_MemberList() : parent(sizeof(SyntaxTree_MemberList))
    {
    }

    SyntaxTree_MemberList::~SyntaxTree_MemberList()
    {
    }

    void SyntaxTree_MemberList::print(ostream& stream, uint indent)const
    {
    }

    // member_desc -> member_desc "." "{Letter}"
    bool Parser::reduceMember2Size()
    {
        SyntaxTree_Name* pName = allocator<SyntaxTree_Name>::allocate();
        construct(pName, shifts.top());

        context.data.insert(pName);

        cout << syntaxTreeStack[1]->type();
        SyntaxTree_MemberList* pMemberList = dynamic_cast<SyntaxTree_MemberList*>(syntaxTreeStack[1]);
        pMemberList->pushChild(pName);

        shifts.pop();
        shifts.pop();
        return true;
    }

    // member_desc -> "{Letter}"
    bool Parser::reduceMember1Size()
    {
        SyntaxTree_Name* pName = allocator<SyntaxTree_Name>::allocate();
        construct(pName, shifts.top());

        context.data.insert(pName);

        SyntaxTree_MemberList* pMemberList = allocator<SyntaxTree_MemberList>::allocate();
        construct(pMemberList);

        context.data.insert(pMemberList);

        pMemberList->pushChild(pName);

        syntaxTreeStack.push(pMemberList);

        shifts.pop();
        return true;
    }
}
