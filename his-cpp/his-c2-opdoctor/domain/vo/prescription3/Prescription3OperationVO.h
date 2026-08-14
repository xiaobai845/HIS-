#pragma once

#ifndef _PRESCRIPTION3_OPERATION_VO_H_
#define _PRESCRIPTION3_OPERATION_VO_H_

#include "../../GlobalInclude.h"
#include "../../dto/prescription3/Prescription3OperationResultDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class Prescription3DeleteJsonVO
    : public JsonVO<Prescription3DeleteResultDTO::Wrapper>
{
    DTO_INIT(Prescription3DeleteJsonVO,
        JsonVO<Prescription3DeleteResultDTO::Wrapper>);

public:
    Prescription3DeleteJsonVO()
    {
        data = Prescription3DeleteResultDTO::createShared();
    }
};

class Prescription3MergeJsonVO
    : public JsonVO<Prescription3MergeResultDTO::Wrapper>
{
    DTO_INIT(Prescription3MergeJsonVO,
        JsonVO<Prescription3MergeResultDTO::Wrapper>);

public:
    Prescription3MergeJsonVO()
    {
        data = Prescription3MergeResultDTO::createShared();
    }
};

class Prescription3SplitJsonVO
    : public JsonVO<Prescription3SplitResultDTO::Wrapper>
{
    DTO_INIT(Prescription3SplitJsonVO,
        JsonVO<Prescription3SplitResultDTO::Wrapper>);

public:
    Prescription3SplitJsonVO()
    {
        data = Prescription3SplitResultDTO::createShared();
    }
};

#include OATPP_CODEGEN_END(DTO)

#endif
