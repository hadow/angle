//
// Copyright (c) 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// AddDefaultReturnStatements.cpp: Add default return statements to functions that do not end in a
//                                 return.
//

#include "compiler/translator/AddDefaultReturnStatements.h"

#include "compiler/translator/IntermNode.h"
#include "compiler/translator/util.h"

namespace sh
{

namespace
{

bool NeedsReturnStatement(TIntermFunctionDefinition *node, TType *returnType)
{
    *returnType = node->getFunctionPrototype()->getType();
    if (returnType->getBasicType() == EbtVoid)
    {
        return false;
    }

    TIntermBlock *bodyNode    = node->getBody();
    TIntermBranch *returnNode = bodyNode->getSequence()->back()->getAsBranchNode();
    if (returnNode != nullptr && returnNode->getFlowOp() == EOpReturn)
    {
        return false;
    }

    return true;
}

}  // anonymous namespace

void AddDefaultReturnStatements(TIntermBlock *root)
{
    TType returnType;
    for (TIntermNode *node : *root->getSequence())
    {
        TIntermFunctionDefinition *definition = node->getAsFunctionDefinition();
        if (definition != nullptr && NeedsReturnStatement(definition, &returnType))
        {
            TIntermBranch *branch =
                new TIntermBranch(EOpReturn, TIntermTyped::CreateZero(returnType));

            TIntermBlock *bodyNode = definition->getBody();
            bodyNode->getSequence()->push_back(branch);
        }
    }
}

}  // namespace sh
