/*
 * RapiSW project.
 *
 * The startingpoint of this project was the INDI Developers Manual Tutorial #5, author Jasem Mutlaq.
 * 
 * This file is part of the RapiSW project.
 * Copyright (c) 2020 Othmar Ehrhardt
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.


*/

#include "basefocuser.h"

#include <memory>
#include <cstring>

BaseFocuser::BaseFocuser(char *thisName)
{
    strcpy(deviceName, thisName);
    FI::SetCapability(FOCUSER_CAN_ABS_MOVE | FOCUSER_CAN_REL_MOVE | FOCUSER_HAS_VARIABLE_SPEED | FOCUSER_HAS_BACKLASH);
}

BaseFocuser::~BaseFocuser()
{
    
}

void BaseFocuser::ISGetProperties(const char *dev)
{
    NDI::DefaultDevice::ISGetProperties(dev);
    defineText(&Outlet1NameTP);
    defineText(&Outlet2NameTP);
    
    loadConfig(true, "OUTLET1_NAME");
    loadConfig(true, "OUTLET2_NAME");
    strcpy(Outlet1SP.label,Outlet1NameT[0].text);
    strcpy(Outlet2SP.label,Outlet2NameT[0].text);
}

void BaseFocuser::ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n)
{
    if (dev != nullptr && strcmp(dev, getDeviceName()) == 0)
    {
        if (strcmp(name, Outlet1SP.name) == 0)
        {
            strcpy(Outlet1SP.label,Outlet1NameT[0].text);
            IUUpdateSwitch(&Outlet1SP, states, names, n);

            if (Outlet1S[0].s == ISS_ON)
            {
                // Here the Rapi GPIO on code
            }
            else
            {
                // Here the Rapi GPIO off code
            }

            Outlet1SP.s = IPS_OK;
            IDSetSwitch(&Outlet1SP, nullptr);
            return true;
        }
        if (strcmp(name, Outlet2SP.name) == 0)
        {
            strcpy(Outlet2SP.label,Outlet2NameT[0].text);
            IUUpdateSwitch(&Outlet2SP, states, names, n);

            if (Outlet2S[0].s == ISS_ON)
            {
                // Here the Rapi GPIO on code
            }
            else
            {
                // Here the Rapi GPIO off code
            }

            Outlet2SP.s = IPS_OK;
            IDSetSwitch(&Outlet2SP, nullptr);
            return true;
        }
    }

    return INDI::DefaultDevice::ISNewSwitch(dev, name, states, names, n);
}

void BaseFocuser::ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n)
{
    if (dev != nullptr && strcmp(dev, getDeviceName()) == 0)
    {
        if (!strcmp(name, Outlet1NameTP.name))
        {
            Outlet1NameTP.s = IPS_OK;
            IText *tp    = IUFindText(&Outlet1NameTP, names[0]);
            IUSaveText(tp, texts[0]);
            IDSetText(&Outlet1NameTP, "Outlet1 name updated");
            return true;
        }
        if (!strcmp(name, Outlet2NameTP.name))
        {
            Outlet2NameTP.s = IPS_OK;
            IText *tp    = IUFindText(&Outlet2NameTP, names[0]);
            IUSaveText(tp, texts[0]);
            IDSetText(&Outlet2NameTP, "Outlet2 name updated");
            return true;
        }
    }

    return INDI::DefaultDevice::ISNewText(dev, name, texts, names, n);
}

void BaseFocuser::ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n)
{
    return INDI::Focuser::ISNewNumber(dev, name, values, names, n);
}

void BaseFocuser::ISNewBLOB(const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[], char *formats[], char *names[], int n)
{
    return INDI::Focuser::ISNewBLOB(dev, name, sizes, blobsizes, blobs, formats, names, n);
}

void BaseFocuser::ISSnoopDevice(XMLEle *root)
{
    return INDI::Focuser::ISSnoopDevice(root);
}

/**************************************************************************************
** Client is asking us to establish connection to the device
***************************************************************************************/
bool BaseFocuser::Connect()
{
    IDMessage(getDeviceName(), "RapiSW box connected successfully!");
    return true;
}

/**************************************************************************************
** Client is asking us to terminate connection to the device
***************************************************************************************/
bool BaseFocuser::Disconnect()
{
    IDMessage(getDeviceName(), "RapiSW box disconnected successfully!");
    return true;
}

/**************************************************************************************
** INDI is asking us for our default device name
***************************************************************************************/
const char *BaseFocuser::getDefaultName()
{
    return deviceName;
}

/**************************************************************************************
** INDI is asking us to init our properties.
***************************************************************************************/
bool BaseFocuser::initProperties()
{
    // Must init parent properties first!
    INDI::DefaultDevice::initProperties();

    IUFillSwitch(&Outlet1S[0], "On", "", ISS_OFF);
    IUFillSwitch(&Outlet1S[1], "Off", "", ISS_OFF);
    IUFillSwitchVector(&Outlet1SP, Outlet1S, 2, getDeviceName(), "PWROUT_1", "Outlet 1", MAIN_CONTROL_TAB, IP_RW, ISR_1OFMANY, 0,
                       IPS_IDLE);
                       
    IUFillSwitch(&Outlet2S[0], "On", "", ISS_OFF);
    IUFillSwitch(&Outlet2S[1], "Off", "", ISS_OFF);
    IUFillSwitchVector(&Outlet2SP, Outlet2S, 2, getDeviceName(), "PWROUT_2", "Outlet 2", MAIN_CONTROL_TAB, IP_RW, ISR_1OFMANY, 0,
                       IPS_IDLE);
                       
    IUFillText(&Outlet1NameT[0], "Name", "", "");
    IUFillTextVector(&Outlet1NameTP, Outlet1NameT, 1, getDeviceName(), "OUTLET1_NAME", "Out1 Name", SITE_TAB, IP_RW, 0, IPS_IDLE);
    
    IUFillText(&Outlet2NameT[0], "Name", "", "");
    IUFillTextVector(&Outlet2NameTP, Outlet2NameT, 1, getDeviceName(), "OUTLET2_NAME", "Out2 Name", SITE_TAB, IP_RW, 0, IPS_IDLE);


    IUFillNumber(&Outlet3N[0], "PWM", "pwm", "%g", 0, 100, 1, 0);
    IUFillNumberVector(&Outlet3NP, Outlet3N, 1, getDeviceName(), "PWM_FREQ", "Outlet 3", MAIN_CONTROL_TAB, IP_RW, 0,
                       IPS_IDLE);
    
    
    
    return true;
}

/********************************************************************************************
** INDI is asking us to update the properties because there is a change in CONNECTION status
* This fucntion is called whenever the device is connected or disconnected.
*********************************************************************************************/
bool BaseFocuser::updateProperties()
{
    // Call parent update properties first
    INDI::DefaultDevice::updateProperties();

    if (isConnected())
    {
        defineSwitch(&Outlet1SP);
        defineSwitch(&Outlet2SP);
        defineNumber(&Outlet3NP);
        defineText(&Outlet1NameTP);
        defineText(&Outlet2NameTP);
    }
    else
    // We're disconnected
    {
        deleteProperty(Outlet1SP.name);
        deleteProperty(Outlet2SP.name);
        deleteProperty(Outlet1NameTP.name);
        deleteProperty(Outlet2NameTP.name);
        deleteProperty(Outlet3NP.name);
    }

    return true;
}

bool BaseFocuser::saveConfigItems(FILE *fp)
{
    INDI::DefaultDevice::saveConfigItems(fp);

    IUSaveConfigText(fp, &Outlet1NameTP);
    IUSaveConfigText(fp, &Outlet2NameTP);

    return true;
}

IPState FocusSim::MoveFocuser(FocusDirection dir, int speed, uint16_t duration)
{
    double mid         = (FocusAbsPosN[0].max - FocusAbsPosN[0].min) / 2;
    int mode           = IUFindOnSwitchIndex(&ModeSP);
    double targetTicks = ((dir == FOCUS_INWARD) ? -1 : 1) * (speed * duration);

    internalTicks += targetTicks;

    if (mode == MODE_ALL)
    {
        if (internalTicks < FocusAbsPosN[0].min || internalTicks > FocusAbsPosN[0].max)
        {
            internalTicks -= targetTicks;
            LOG_ERROR("Cannot move focuser in this direction any further.");
            return IPS_ALERT;
        }
    }

    // simulate delay in motion as the focuser moves to the new position
    usleep(duration * 1000);

    double ticks = initTicks + (internalTicks - mid) / 5000.0;

    FWHMN[0].value = 0.5625 * ticks * ticks + SeeingN[0].value;

    LOGF_DEBUG("TIMER Current internal ticks: %g FWHM ticks: %g FWHM: %g", internalTicks, ticks,
               FWHMN[0].value);

    if (mode == MODE_ALL)
    {
        FocusAbsPosN[0].value = internalTicks;
        IDSetNumber(&FocusAbsPosNP, nullptr);
    }

    if (FWHMN[0].value < SeeingN[0].value)
        FWHMN[0].value = SeeingN[0].value;

    IDSetNumber(&FWHMNP, nullptr);

    return IPS_OK;
}

/************************************************************************************
 *
************************************************************************************/
IPState BaseFocuser::MoveAbsFocuser(uint32_t targetTicks)
{

    return IPS_OK;
}

/************************************************************************************
 *
************************************************************************************/
IPState BaseFocuser::MoveRelFocuser(FocusDirection dir, uint32_t ticks)
{
    
    return IPS_OK;
}

/************************************************************************************
 *
************************************************************************************/
bool BaseFocuser::SetFocuserSpeed(int speed)
{
    INDI_UNUSED(speed);
    return true;
}

/************************************************************************************
 *
************************************************************************************/
bool BaseFocuser::SetFocuserBacklash(int32_t steps)
{
    INDI_UNUSED(steps);
    return true;
}

/************************************************************************************
 *
************************************************************************************/
bool BaseFocuser::SetFocuserBacklashEnabled(bool enabled)
{
    INDI_UNUSED(enabled);
    return true;
}
