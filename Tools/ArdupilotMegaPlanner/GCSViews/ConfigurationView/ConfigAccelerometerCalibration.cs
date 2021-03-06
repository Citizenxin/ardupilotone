﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ArdupilotMega.Controls.BackstageView;

namespace ArdupilotMega.GCSViews.ConfigurationView
{
    public partial class ConfigAccelerometerCalibration : BackStageViewContentPanel
    {
        public ConfigAccelerometerCalibration()
        {
            InitializeComponent();
        }

        private void pictureBoxQuadX_Click(object sender, EventArgs e)
        {
            try
            {
                MainV2.comPort.setParam("FRAME", 1f);
                CustomMessageBox.Show("Set to x");
            }
            catch { CustomMessageBox.Show("Set frame failed"); }
        }

        private void BUT_levelac2_Click(object sender, EventArgs e)
        {
            try
            {
#if MAVLINK10
                int fixme; // needs to be accel only
                MainV2.comPort.doCommand(MAVLink.MAV_CMD.PREFLIGHT_CALIBRATION,1,1,1,1,1,1,1);
#else
                MainV2.comPort.doAction(MAVLink.MAV_ACTION.MAV_ACTION_CALIBRATE_ACC);
#endif

                BUT_levelac2.Text = "Complete";
            }
            catch
            {
                CustomMessageBox.Show("Failed to level : ac2 2.0.37+ is required");
            }
        }

        private void pictureBoxQuad_Click(object sender, EventArgs e)
        {
            try
            {
                MainV2.comPort.setParam("FRAME", 0f);
                CustomMessageBox.Show("Set to +");
            }
            catch { CustomMessageBox.Show("Set frame failed"); }
        }

        private void ConfigAccelerometerCalibration_Load(object sender, EventArgs e)
        {
            if (!MainV2.comPort.BaseStream.IsOpen)
            {
                this.Enabled = false;
                return;
            }
            else
            {
                this.Enabled = true;
            }
        }
    }
}
