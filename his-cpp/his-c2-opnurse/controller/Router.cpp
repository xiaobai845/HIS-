/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/03 14:58:34

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "Router.h"
#include "ApiHelper.h"

#include"patient/PatientController.h"

#include "nurse2/NurseController2.h"

#include"patient/PatientActController.h"
#include"patient/PatientConsumController.h"

// If the macro for disabling Swagger documentation is defined



#include "opnurse/PrintJobController.h"
#include "opnurse/PrintLogController.h"

#ifdef CLOSE_SWAGGER_DOC
#define ROUTER_SIMPLE_BIND(__CLASS__) \
router->addController(__CLASS__::createShared())
#else
#define ROUTER_SIMPLE_BIND(__CLASS__) \
BIND_CONTROLLER(docEndpoints, router, __CLASS__)
#endif

Router::Router(Endpoints* docEndpoints, HttpRouter* router)
{
	this->docEndpoints = docEndpoints;
	this->router = router;
}

void Router::initRouter()
{
	ROUTER_SIMPLE_BIND(PrintJobController);
	// #TIP: Add system extension route definitions below

	ROUTER_SIMPLE_BIND(PatientController);

	ROUTER_SIMPLE_BIND(NurseController2);


	ROUTER_SIMPLE_BIND(PatientActController);
	ROUTER_SIMPLE_BIND(PatientConsumController);

}
