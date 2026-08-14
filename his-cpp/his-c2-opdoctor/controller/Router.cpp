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


#include "prescription2/Prescription2Controller.h"

#include "chinapres1/ChinapresController1.h"
#include"outpatientrecord/MedicalRecordController.h"

#include "prescription4/historyOrderDetailController.h"
#include "prescription4/historyOrderListController.h"



#include "cycleCtrl1/PatientQueueController.h"
#include "cycleCtrl1/ReceptionPatientController.h"
#include "cycleCtrl1/PatientFinishController.h"
#include "cycleCtrl1/PatientLeaveController.h"


#include "controller/diagnose/DiagnoseController.h"

#include"cycleCtrl2/RefundController.h"
#include"cycleCtrl2/PrescriptionController.h"
#include"cycleCtrl2/AdmissionController.h"


#include "controller/prescription3/Prescription3Controller.h"



#include "order/OrderController1.h"


#include "chinapres2/Chinapres2Controller.h"

#include "chinapres3/chinapres3Controller.h"
#include "outpatientrecord3/outpatientrecord3Controller.h"
#include "outpatientrecord2/OutpatientRecordController.h"


// If the macro for disabling Swagger documentation is defined
#ifdef CLOSE_SWAGGER_DOC
// Simplified controller binding macro
#define ROUTER_SIMPLE_BIND(__CLASS__) \
router->addController(__CLASS__::createShared())
#else
// Simplified controller binding macro (with Swagger support)
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
	// #TIP: Add system extension route definitions below

	ROUTER_SIMPLE_BIND(PatientQueueController);
	ROUTER_SIMPLE_BIND(RecePatientController);
	ROUTER_SIMPLE_BIND(PatientFinishController);
	ROUTER_SIMPLE_BIND(PatientLeaveController);

	ROUTER_SIMPLE_BIND(DiagnoseController);


	ROUTER_SIMPLE_BIND(Refund2Controller);
	ROUTER_SIMPLE_BIND(PrescriptionController2);
	ROUTER_SIMPLE_BIND(Admission2Controller);


	ROUTER_SIMPLE_BIND(Prescription3Controller);


	ROUTER_SIMPLE_BIND(HistoryOrderListController);
	ROUTER_SIMPLE_BIND(HistoryOrderDetailController);


	ROUTER_SIMPLE_BIND(ChinapresController1);
	ROUTER_SIMPLE_BIND(MedicalRecordController);
	ROUTER_SIMPLE_BIND(Chinapres2Controller);

	ROUTER_SIMPLE_BIND(chinapres3Controller);

	ROUTER_SIMPLE_BIND(Prescription2Controller);

	ROUTER_SIMPLE_BIND(OrderController1);

	ROUTER_SIMPLE_BIND(OutpatientRecordController);

	ROUTER_SIMPLE_BIND(outpatientrecord33Controller);
}
