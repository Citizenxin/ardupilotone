#ifndef _APO_COMMON_H
#define _APO_COMMON_H

FastSerialPort0(Serial);
FastSerialPort1(Serial1);
FastSerialPort2(Serial2);
FastSerialPort3(Serial3);

/*
 * Required Global Declarations
 */

static apo::AP_Autopilot * autopilot;

void setup() {

    using namespace apo;

    // hardware abstraction layer
    AP_Board * board = new BOARD_TYPE(parameters);

    /*
     * Select guidance, navigation, control algorithms
     */
    AP_Navigator * navigator = NULL;

    if (board->getParameters().mode == AP_Board::MODE_LIVE) {
        navigator = new NAVIGATOR_CLASS(board,k_nav);
    } else {
        navigator = new AP_Navigator(board);
    }

    AP_Guide * guide = new GUIDE_CLASS(navigator, board, velCmd, xt, xtLim);
    AP_Controller * controller = new CONTROLLER_CLASS(navigator,guide,board);

    board->setGcs(new MavlinkComm(AP_Board::PORT_GCS,navigator,guide,controller,board)); 
    if (board->getParameters().mode != AP_Board::MODE_LIVE) {
        board->setHil(new MavlinkComm(AP_Board::PORT_HIL,navigator,guide,controller,board)); 
    }

    /*
     * Start the autopilot
     */
    autopilot = new apo::AP_Autopilot(navigator, guide, controller, board);
}

void loop() {
    autopilot->update();
}

#endif //_APO_COMMON_H
// vim:ts=4:sw=4:expandtab
