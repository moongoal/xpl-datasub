//https://developer.x-plane.com/wp-content/plugins/code-sample-generation/sample_templates/XPSDK303.zip
#include <XPLM/XPLMDefs.h>
#include <XPLM/XPLMPlugin.h>
#include <XPLM/XPLMProcessing.h>
#include "service.h"
#include "drefs.h"

// Number of seconds between each callback call
#define CALLBACK_INTERVAL 5.0f

XPLMFlightLoopID flightloop_id;

float flightloop_clbk(
    float inElapsedSinceLastCall,
    float inElapsedTimeSinceLastFlightLoop,
    int inCounter,
    void * inRefcon) {
        service_loop_once();

        return CALLBACK_INTERVAL;
}

PLUGIN_API int XPluginStart(char *outName, char *outSignature, char *outDescription) {
    // Register plugin
    strcpy(outName, "Data Subscriber");
    strcpy(outSignature, "moongoal.datasub");
    strcpy(outDescription, "Dataref subscription service");

    // Register flight loop callback
    XPLMCreateFlightLoop_t loop_def;

    loop_def.structSize = sizeof(XPLMCreateFlightLoop_t);
    loop_def.phase = xplm_FlightLoop_Phase_AfterFlightModel;
    loop_def.callbackFunc = flightloop_clbk;
    loop_def.refcon = NULL;

    flightloop_id = XPLMCreateFlightLoop(&loop_def);

    return 1; // OK
}

PLUGIN_API int XPluginEnable(void) {
    start_service();

    return 1; // OK
}

PLUGIN_API void XPluginDisable(void) {
    shutdown_service();
    free_sub_drefs();
}

PLUGIN_API void XPluginStop(void) {
    XPLMDestroyFlightLoop(flightloop_id);
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMessage, void *inParam) {
    switch(inMessage) {
        case XPLM_MSG_PLANE_LOADED:
            const int plane_id = (int)inParam;

            if(plane_id == 0) {
                // New user plane loaded
            }

            break;
    }
}
