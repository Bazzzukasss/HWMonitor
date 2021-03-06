#ifndef UDPCLIENT_EDDYCONC_H
#define UDPCLIENT_EDDYCONC_H

#include <QObject>
#include <QString>
#include <QUdpSocket>
#include "NetUDPClient_Linpack.h"
#include "NetPacket.h"
#include "NetDevice.h"


enum RustaviCommandsEnum
{
    LP_CMD_ROLGANG_FWD,
    LP_CMD_ROLGANG_BWD,
    LP_CMD_MAB1_WORK,
    LP_CMD_MAB1_WATER,
    LP_CMD_MAB2_WORK,
    LP_CMD_MAB2_WATER,
    LP_CMD_MAB3_WORK,
    LP_CMD_MAB3_WATER,
    LP_CMD_MAB4_WORK,
    LP_CMD_MAB4_WATER,

    LP_CMD_ERROR,
    LP_CMD_READY,
    LP_CMD_RES_OK,
    LP_CMD_RES_BRK,
    LP_CMD_PROCESS,
    LP_CMD_MAB1_MASK,
    LP_CMD_MAB2_MASK,
    LP_CMD_MAB3_MASK,
    LP_CMD_MAB4_MASK
};

enum RustaviStateModulesEnum
{
    LP_ST_DM_RUSTAVI_SLOT_0,
    LP_ST_DM_RUSTAVI_SLOT_1,
    LP_ST_DM_RUSTAVI_SLOT_2,
    LP_ST_DM_RUSTAVI_SLOT_3,
    LP_ST_DM_RUSTAVI_SLOT_4,
    LP_ST_DM_RUSTAVI_SLOT_5,
    LP_ST_DM_RUSTAVI_SLOT_6,
    LP_ST_DM_RUSTAVI_SLOT_7,
    LP_ST_DM_RUSTAVI_SLOT_8,
    LP_ST_DM_RUSTAVI_SLOT_9,
    LP_ST_DM_RUSTAVI_MEM_1,
    LP_ST_DM_RUSTAVI_MEM_2,
    LP_ST_DM_RUSTAVI_1,
    LP_ST_DM_RUSTAVI_2,
    LP_ST_AM_RUSTAVI_1,
    PC_DM_RUSTAVI_1,
    PC_DM_RUSTAVI_2
};
enum RustaviStateEnum
{

///SLOT 0
    LP_ST_ASU_PIPE_LOADING,
    LP_ST_CLEANER_HOME,
    LP_ST_POST_CLEANER_BEGIN,
    LP_ST_POST_CLEANER_END,
    LP_ST_POST_MAB1_BEGIN,
    LP_ST_POST_MAB1_END,
    LP_ST_POST_MAB2_END,
    LP_ST_POST_MAB1_WORK,
    LP_ST_POST_MAB2_WORK,
    LP_ST_POST_MAB1_HOME,
    LP_ST_POST_MAB2_HOME,
    LP_ST_POST_MAB3_BEGIN,
    LP_ST_POST_MAB3_END,
    LP_ST_POST_MAB4_END,
    LP_ST_POST_MAB3_WORK,
    LP_ST_POST_MAB4_WORK,
    LP_ST_POST_MAB3_HOME,
    LP_ST_POST_MAB4_HOME,
    LP_ST_POST_DP1_BEGIN,
    LP_ST_POST_DP1_END,
    LP_ST_DEVICE_LEVEL,
    LP_ST_POST_PR1_HOME,
    LP_ST_POST_PR1_WORK,
    LP_ST_POST_PR2_HOME,
    LP_ST_POST_PR2_WORK,
    LP_ST_POST_PR3_HOME,
    LP_ST_POST_PR3_WORK,
    LP_ST_POST_PR4_HOME,
    LP_ST_POST_PR4_WORK,
    LP_ST_ASU_PIPE_UPLOADING,
    LP_ST_BTN_ERROR_STOP,
    LP_ST_RESERV1,
///SLOT 1
    LP_ST_RESERV2,
    LP_ST_SWITCH_RESOLUTION,
    LP_ST_SWITCH_SETUP,
    LP_ST_SWITCH_WORK,
    LP_ST_SWITCH_TRANSITE,
    LP_ST_BTN_LOAD_PIPE,
    LP_ST_BTN_UPLOAD_PIPE,
    LP_ST_SWITCH_ON_CLEANER,
    LP_ST_SWITCH_ROLLER_FORTH,
    LP_ST_SWITCH_ROLLER_BACK,
    LP_ST_BTN_ROLLER_SLOW,
    LP_ST_BTN_ROLLER_FAST,
    LP_ST_BTN_SPIRAL_SLOW,
    LP_ST_BTN_SPIRAL_FAST,
    LP_ST_BTN_UZK1_WATER,
    LP_ST_BTN_UZK2_WATER,
    LP_ST_BTN_PR1_ON_WORK,
    LP_ST_BTN_PR1_ON_HOME,
    LP_ST_BTN_MAB1_ON_WORK,
    LP_ST_BTN_MAB1_ON_HOME,
    LP_ST_BTN_MAB2_ON_WORK,
    LP_ST_BTN_MAB2_ON_HOME,
    LP_ST_BTN_PR2_ON_WORK,
    LP_ST_BTN_PR2_ON_HOME,
    LP_ST_BTN_PR3_ON_WORK,
    LP_ST_BTN_PR3_ON_HOME,
    LP_ST_BTN_MAB3_ON_WORK,
    LP_ST_BTN_MAB3_ON_HOME,
    LP_ST_BTN_MAB4_ON_WORK,
    LP_ST_BTN_MAB4_ON_HOME,
    LP_ST_BTN_PR4_ON_WORK,
    LP_ST_BTN_PR4_ON_HOME,
///SLOT 2
    LP_ST_AC_SUPPLY,
    LP_ST_AV_AC_SUPPLY_ON,
    LP_ST_AV_CLEANER1_ON,
    LP_ST_AV_CLEANER2_ON,
    LP_ST_AV_PUMP_ON,
    LP_ST_AV_PUMP_STATION1_ON,
    LP_ST_AV_PUMP_STATION2_ON,
    LP_ST_CONTACTOR_CLEANER1_ON,
    LP_ST_CONTACTOR_CLEANER2_ON,
    LP_ST_CONTACTOR_PUMP_ON,
    LP_ST_CONTACTOR_PUMP_STATION1_ON,
    LP_ST_CONTACTOR_PUMP_STATION2_ON,
    LP_ST_RESERV3,
    LP_ST_RESERV4,
    LP_ST_RESERV5,
    LP_ST_RESERV6,
///SLOT 3
    LP_ST_LED_LOADING_PERMITTED,
    LP_ST_LED_UPLOADING_PERMITTED,
    LP_ST_LED_ROLLER_SLOW,
    LP_ST_LED_ROLLER_FAST,
    LP_ST_LED_SPIRAL_SLOW,
    LP_ST_LED_SPIRAL_FAST,
    LP_ST_LED_UZK1_WATER,
    LP_ST_LED_UZK2_WATER,
    LP_ST_LED_BRAK,
    LP_ST_LED_GODEN,
    LP_ST_LED_ERROR_STOP,
    LP_ST_OUT_RESERV1,
    LP_ST_OUT_RESERV2,
    LP_ST_OUT_RESERV3,
    LP_ST_OUT_RESERV4,
    LP_ST_OUT_RESERV5,
///SLOT 4
    LP_ST_OUT_MAB1_ON_WORK,
    LP_ST_OUT_MAB1_ON_HOME,
    LP_ST_OUT_MAB2_ON_WORK,
    LP_ST_OUT_MAB2_ON_HOME,
    LP_ST_OUT_MAB3_ON_WORK,
    LP_ST_OUT_MAB3_ON_HOME,
    LP_ST_OUT_MAB4_ON_WORK,
    LP_ST_OUT_MAB4_ON_HOME,
    LP_ST_OUT_PR1_ON_WORK,
    LP_ST_OUT_PR1_ON_HOME,
    LP_ST_OUT_PR2_ON_WORK,
    LP_ST_OUT_PR2_ON_HOME,
    LP_ST_OUT_PR3_ON_WORK,
    LP_ST_OUT_PR3_ON_HOME,
    LP_ST_OUT_PR4_ON_WORK,
    LP_ST_OUT_PR4_ON_HOME,
///SLOT 5
    LP_ST_OUT_CLEANER_ON,
    LP_ST_OUT_PUMP1_STATION_ON,
    LP_ST_OUT_PUMP2_STATION_ON,
    LP_ST_OUT_PUMP_ON,
    LP_ST_ASU_ERROR_STOP,
    LP_ST_ASU_EXTRACT_ON,
    LP_ST_ASU_LOAD_PIPE,
    LP_ST_ASU_UPLOAD_PIPE,
    LP_ST_ASU_ROLLER_FORTH,
    LP_ST_ASU_ROLLER_BACK,
    LP_ST_ASU_ROLLER_SLOW,
    LP_ST_ASU_ROLLER_FAST,
    LP_ST_ASU_SPIRAL_SLOW,
    LP_ST_ASU_SPIRAL_FAST,
    LP_ST_ASU_BRAK,
    LP_ST_ASU_GODEN,
    LP_ST_OUT_WATER1_ON,
    LP_ST_OUT_WATER2_ON,
    LP_ST_OUT_WATER3_ON,
    LP_ST_OUT_WATER4_ON,
    LP_ST_OUT_WATER_PIPES_OPEN,
    LP_ST_OUT_CLEAN_FLAP_OPEN,
    LP_ST_OUT_RESERV6,
    LP_ST_OUT_RESERV7,
    LP_ST_OUT_ASD_LIGHT_R,
    LP_ST_OUT_ASD_LIGHT_Y,
    LP_ST_OUT_ASD_LIGHT_G,
    LP_ST_OUT_ASD_BEEP,
    LP_ST_OUT_RESERV8,
    LP_ST_OUT_RESERV9,
    LP_ST_OUT_RESERV10,
    LP_ST_OUT_RESERV11,
///SLOT 6
    LP_ST_WATER_LEVEL1,
    LP_ST_WATER_LEVEL2,
///SLOT 7
///SLOT 8
    LP_ST_DIP_SWITCH_1_DEBUG_EXIT,
    LP_ST_DIP_SWITCH_2_SETUP_MOD_DEBUG,
    LP_ST_DIP_SWITCH_3,
    LP_ST_DIP_SWITCH_4_ENABLE_BEEP,
    LP_ST_DIP_SWITCH_5_WATER_CONDITIONING,
    LP_ST_DIP_SWITCH_6_ENABLE_ERROE_LEVEL,
    LP_ST_DIP_SWITCH_7_ENABLE_ERROE_STOP,
    LP_ST_DIP_SWITCH_8_ENABLE_CHECK_POWER_AV,
///SLOT 9
    LP_ST_ROLLER_SPEED1,
    LP_ST_ROLLER_SPEED2,
    LP_ST_ROLLER_SPEED3,
    LP_ST_ROLLER_SPEED4,
///MEM 1
    LP_ST_LOCAL_BLIT,
    LP_ST_LOCAL_NBLIT,
    LP_ST_LOCAL_ERROR,
    LP_ST_EXTERN_ERROR,
    LP_ST_LOCAL_RES_OK,
    LP_ST_LOCAL_RES_BRK,
    LP_ST_LOCAL_CONTROL_ENABLE,
    LP_ST_LOCAL_PIPE_NPOSTLOAD,
    LP_ST_LOCAL_MABS_INITED,
    LP_ST_LOCAL_PRS_INITED,
    LP_ST_LOCAL_PIPE_LOADED,
    LP_ST_LOCAL_PIPE_UPLOADED,
    LP_ST_LOCAL_PIPE_PRESENT,
    LP_ST_LOCAL_PIPE_POS0,
    LP_ST_LOCAL_PIPE_POS1,
    LP_ST_LOCAL_PIPE_POS2,
    LP_ST_LOCAL_PIPE_POS3,
    LP_ST_LOCAL_PIPE_POS4,
    LP_ST_LOCAL_PIPE_POS5,
    LP_ST_LOCAL_PIPE_POS6,
    LP_ST_LOCAL_PIPE_POS7,
    LP_ST_LOCAL_PIPE_POS8,
    LP_ST_LOCAL_PIPE_POS9,
    LP_ST_LOCAL_PIPE_POS10,
    LP_ST_LOCAL_PIPE_POS11,
///MEM2
    LP_ST_LOCAL_MAB1_INIT,
    LP_ST_LOCAL_MAB2_INIT,
    LP_ST_LOCAL_MAB3_INIT,
    LP_ST_LOCAL_MAB4_INIT,
    LP_ST_LOCAL_PR1_INIT,
    LP_ST_LOCAL_PR2_INIT,
    LP_ST_LOCAL_PR3_INIT,
    LP_ST_LOCAL_PR4_INIT,
    LP_ST_LOCAL_MAB1_HOME,
    LP_ST_LOCAL_MAB2_HOME,
    LP_ST_LOCAL_MAB3_HOME,
    LP_ST_LOCAL_MAB4_HOME,
    LP_ST_LOCAL_PR1_HOME,
    LP_ST_LOCAL_PR2_HOME,
    LP_ST_LOCAL_PR3_HOME,
    LP_ST_LOCAL_PR4_HOME,
    LP_ST_LOCAL_MAB1_WORK,
    LP_ST_LOCAL_MAB2_WORK,
    LP_ST_LOCAL_MAB3_WORK,
    LP_ST_LOCAL_MAB4_WORK,
    LP_ST_LOCAL_PR1_WORK,
    LP_ST_LOCAL_PR2_WORK,
    LP_ST_LOCAL_PR3_WORK,
    LP_ST_LOCAL_PR4_WORK,
    LP_ST_LOCAL_MAB1_WATER_ON,
    LP_ST_LOCAL_MAB2_WATER_ON,
    LP_ST_LOCAL_MAB3_WATER_ON,
    LP_ST_LOCAL_MAB4_WATER_ON,
///MODULE LP_ST_DM_RUSTAVI_1
    LP_ST_ROLGANG_FWD,
    LP_ST_ROLGANG_BWD,
    LP_ST_MAB1_WORK,
    LP_ST_MAB1_WATER,
    LP_ST_MAB2_WORK,
    LP_ST_MAB2_WATER,
    LP_ST_MAB3_WORK,
    LP_ST_MAB3_WATER,
    LP_ST_MAB4_WORK,
    LP_ST_MAB4_WATER,
    LP_ST_MAB1_BEG,
    LP_ST_MAB2_BEG,
    LP_ST_MAB3_BEG,
    LP_ST_MAB4_BEG,
///MODULE LP_ST_DM_RUSTAVI_2
    LP_ST_CNTRL_MODE0,
    LP_ST_CNTRL_MODE1,
    LP_ST_CNTRL_ERROR_STOP,
    LP_ST_CNTRL_ERROR_LEVEL,
    LP_ST_CNTRL_RESERV1,
    LP_ST_CNTRL_LOAD,
    LP_ST_CNTRL_UPLOAD,
    LP_ST_CNTRL_LOAD_OK,
    LP_ST_CNTRL_UPLOAD_OK,
    LP_ST_CNTRL_MAB1_PWORK,
    LP_ST_CNTRL_MAB2_PWORK,
    LP_ST_CNTRL_MAB3_PWORK,
    LP_ST_CNTRL_MAB4_PWORK,
    LP_ST_CNTRL_MAB1_WORK,
    LP_ST_CNTRL_MAB2_WORK,
    LP_ST_CNTRL_MAB3_WORK,
    LP_ST_CNTRL_MAB4_WORK,
    LP_ST_CNTRL_PR1_WORK,
    LP_ST_CNTRL_PR2_WORK,
    LP_ST_CNTRL_PR3_WORK,
    LP_ST_CNTRL_PR4_WORK,
    LP_ST_CNTRL_MEAS_LEN_OK,
///MODULE LP_ST_AM_RUSTAVI_1
    LP_ST_UDP_ERROR_CODE,
    LP_ST_UDP_WATER_LEVEL1,
    LP_ST_UDP_WATER_LEVEL2,
    LP_ST_UDP_SPEED_LEN,
    LP_ST_UDP_PIPE_LEN,
    LP_ST_UDP_ZONE_MAB1_ON,
    LP_ST_UDP_ZONE_MAB2_ON,
    LP_ST_UDP_ZONE_MAB3_ON,
    LP_ST_UDP_ZONE_MAB4_ON,
    LP_ST_UDP_ZONE_MAB1_OFF,
    LP_ST_UDP_ZONE_MAB2_OFF,
    LP_ST_UDP_ZONE_MAB3_OFF,
    LP_ST_UDP_ZONE_MAB4_OFF,
///PC_DM_RUSTAVI_1
    LP_ST_PC_ROLGANG_FWD,
    LP_ST_PC_ROLGANG_BWD,
    LP_ST_PC_MAB1_WORK,
    LP_ST_PC_MAB1_WATER,
    LP_ST_PC_MAB2_WORK,
    LP_ST_PC_MAB2_WATER,
    LP_ST_PC_MAB3_WORK,
    LP_ST_PC_MAB3_WATER,
    LP_ST_PC_MAB4_WORK,
    LP_ST_PC_MAB4_WATER,
///PC_DM_RUSTAVI_2
    LP_ST_PC_ERROR,
    LP_ST_PC_READY,
    LP_ST_PC_RES_OK,
    LP_ST_PC_RES_BRK,
    LP_ST_PC_PROCESS,
    LP_ST_PC_MAB1_MASK,
    LP_ST_PC_MAB2_MASK,
    LP_ST_PC_MAB3_MASK,
    LP_ST_PC_MAB4_MASK
};

class NetUDPClient_Linpack_Rustavi : public NetUDPClient_Linpack
{
    Q_OBJECT
    public:
        explicit NetUDPClient_Linpack_Rustavi(const QString& _ip, int _port,QObject *parent);
        ~NetUDPClient_Linpack_Rustavi();
        void send_CMD_SET(bool _is_emulation=false);
    private:
        void init();
};

#endif // UDPCLIENT_EDDYCONC_H
