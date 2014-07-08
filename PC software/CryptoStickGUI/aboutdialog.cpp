/*
* Author: Copyright (C)  Rudolf Boeddeker  Date: 2014-04-12
*
* This file is part of GPF Crypto Stick.
*
* GPF Crypto Stick is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* GPF Crypto Stick is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with GPF Crypto Stick. If not, see <http://www.gnu.org/licenses/>.
*/

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include "stick20infodialog.h"
#include "stick20responsedialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QPixmap image(":/images/CS_icon.png");
    QPixmap small = image.scaled(70,70,Qt::KeepAspectRatio,Qt::FastTransformation);

    ui->IconLabel->setPixmap(small);

//    showStick20Configuration ();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_ButtonOK_clicked()
{
    done (TRUE);
}


/*******************************************************************************

  GetStick20Status

  Changes
  Date      Author        Info
  17.04.14  RB            Function created

  Reviews
  Date      Reviewer        Info

*******************************************************************************/

void AboutDialog::GetStick20Status (void)
{
    bool ret;
    int  Result;

    ret = cryptostick->stick20GetStatusData ();

// Wait for response
    Stick20ResponseDialog ResponseDialog(this);

    ResponseDialog.NoStopWhenStatusOK ();
    ResponseDialog.NoShowDialog();
    ResponseDialog.hide();

    ResponseDialog.cryptostick=cryptostick;
    ResponseDialog.open();
//    ResponseDialog.exec();
    Result = ResponseDialog.ResultValue;
}

/*******************************************************************************

  showStick20Configuration

  Changes
  Date      Author        Info
  02.07.14  RB            Function created

  Reviews
  Date      Reviewer        Info

*******************************************************************************/

void AboutDialog::showStick20Configuration (void)
{
    QString OutputText;
/*
    OutputText.append(QString("Crypto Stick Storage status\n\n"));
*/
    if (false == cryptostick->activStick20)
    {
        OutputText.append(QString("*** No Crypto Stick Storage found ***\n"));
        ui->DeviceStatusLabel->setText(OutputText);
        return;
    }

    GetStick20Status ();
/*
    OutputText.append(QString("Firmware version     "));
    OutputText.append(QString("%1").arg(QString::number(HID_Stick20Configuration_st.VersionInfo_au8[0])));
    OutputText.append(QString("."));
    OutputText.append(QString("%1").arg(QString::number(HID_Stick20Configuration_st.VersionInfo_au8[1])));
    OutputText.append(QString("\n"));
*/
    if (TRUE == HID_Stick20Configuration_st.StickKeysNotInitiated)
    {
        OutputText.append(QString(" ***  Warning stick is not securce  ***")).append("\n");
        OutputText.append(QString(" **  Select -Init encrypted volumes- **")).append("\n").append("\n");
    }

/*
    if (TRUE == HID_Stick20Configuration_st.FirmwareLocked_u8)
    {
        OutputText.append(QString("*** Firmware is locked *** ")).append("\n");
    }

    if (READ_WRITE_ACTIVE == HID_Stick20Configuration_st.ReadWriteFlagUncryptedVolume_u8)
    {
        OutputText.append(QString("Unencrypted volume   READ/WRITE mode ")).append("\n");
    }
    else
    {
        OutputText.append(QString("Unencrypted volume   READ ONLY mode ")).append("\n");
    }
*/


/*
    OutputText.append(QString("SD change counter    "));
    OutputText.append(QString("%1").arg(QString::number(HID_Stick20Configuration_st.NewSDCardFound_u8 >> 1))).append("\n");

    OutputText.append(QString("SD erase counter     "));
    OutputText.append(QString("%1").arg(QString::number(HID_Stick20Configuration_st.SDFillWithRandomChars_u8 >> 1))).append("\n");


    OutputText.append(QString("\n"));
    OutputText.append(QString("SD card infos\n"));

    OutputText.append(QString(" ID     0x"));
    OutputText.append(QString("%1").arg(QString::number(HID_Stick20Configuration_st.ActiveSD_CardID_u32,16))).append("\n");
*/

    if (0 != (HID_Stick20Configuration_st.NewSDCardFound_u8 & 0x01))
    {
        OutputText.append(QString(" *** New SD card found ***\n"));
    }

    if (0 == (HID_Stick20Configuration_st.SDFillWithRandomChars_u8 & 0x01))
    {
        OutputText.append(QString(" *** Not erased with random chars ***\n"));
    }

    OutputText.append(QString("\n"));

    if (0 != (HID_Stick20Configuration_st.VolumeActiceFlag_u8 & (1 << SD_CRYPTED_VOLUME_BIT_PLACE)))
    {
        OutputText.append(QString("Encrypted volume     active")).append("\n");
    }
    else
    {
        OutputText.append(QString("Encrypted volume     not active")).append("\n");
    }

    if (0 != (HID_Stick20Configuration_st.VolumeActiceFlag_u8 & (1 << SD_HIDDEN_VOLUME_BIT_PLACE)))
    {
        OutputText.append(QString("Hidden volume        active")).append("\n");
    }

    OutputText.append(QString("\n"));
/*
    OutputText.append(QString("Smartcard infos\n"));

    OutputText.append(QString(" ID     0x"));
    OutputText.append(QString("%1").arg(QString::number(HID_Stick20Configuration_st.ActiveSmartCardID_u32,16))).append("\n");
*/
    OutputText.append(QString("Password retry counter\n"));
    OutputText.append(QString("Admin : "));
    OutputText.append(QString("%1").arg(QString::number(HID_Stick20Configuration_st.AdminPwRetryCount))).append("\n");

    OutputText.append(QString("User  : "));
    OutputText.append(QString("%1").arg(QString::number(HID_Stick20Configuration_st.UserPwRetryCount))).append("\n");

    ui->DeviceStatusLabel->setText(OutputText);
}

void AboutDialog::on_ButtonStickStatus_clicked()
{
    Stick20InfoDialog InfoDialog(this);
    InfoDialog.exec();
}
