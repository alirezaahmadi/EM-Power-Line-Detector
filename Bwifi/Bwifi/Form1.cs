using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Security.Cryptography;
using System.Threading;
using System.IO.Ports;

using ZedGraph;

namespace Bwifi
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        SerialPort SD_Com;
        string[] _com = new string[10];

        List<string> _items = new List<string>();
        UdpClient listener = new UdpClient(50000);
        IPEndPoint groupEP = new IPEndPoint(IPAddress.Any, 50000);
        byte[] bytes = { 0 };
        int i = 0;
        GraphPane Pane;
        LineItem Heart_rate_curve;
        short Heart_rate = 0;
        List<double> B = new List<double>();
        bool SD_Com_en = false;
        
        private void Form1_Load(object sender, EventArgs e)
        {
            Pane = ZG.GraphPane;
            Heart_rate_curve = Pane.AddCurve("Power Rate", null, Color.Red, SymbolType.None);
        }
        private void button1_Click(object sender, EventArgs e)
        {
            Action UDP = new Action(() => 
            {
                while(true)
                {
                    try
                    {
                        double x = 0;
                        bytes = listener.Receive(ref groupEP);

                        Thread.Sleep(1);

                        if (i < (bytes.GetLength(0) - 1)) i++;
                        if (i > 65535) i = 0;

                        Heart_rate = bytes[i];
                        if (Heart_rate < 90 && Heart_rate > 50)
                            B.Add(Heart_rate);
                        x = Heart_rate_curve.Points.Count;
                        Heart_rate_curve.AddPoint(x, B[(B.Count - 1)]);
                        ZG.AxisChange();
                        ZG.Invalidate();
                    }
                    catch
                    {

                    }
                }     
            });
            UDP.BeginInvoke(null, null);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (Heart_rate < 90 && Heart_rate > 50)
            label2.Text = bytes[i].ToString();
        }

        private void toolStripComboBox1_Click(object sender, EventArgs e)
        {

        }

        private void toolStripComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void btn_Connect_Click(object sender, EventArgs e)
        {

        }

        private void _Start()
        {
            toolStripComboBox1.Items.Clear();
            toolStripComboBox1.Items.Add("Auto Search");
            toolStripComboBox1.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
            //###################################################################

            #region Port OPEN
            if (btn_Connect.ToolTipText == "Open")
            {
                _com = System.IO.Ports.SerialPort.GetPortNames();
                if (_com.Count() == 0)
                {
                    MessageBox.Show("Connect PRC to PC !!","Error");
                }
                else
                {
                    try
                    {
                        for (int cnt = 0; cnt < toolStripComboBox1.Items.Count; cnt++)
                        {
                            SD_Com = new SerialPort(_com[cnt], 115200);
                            Thread.Sleep(1);
                            if (SD_Com.IsOpen == false)
                            {
                                try
                                {
                                    SD_Com.ReadTimeout = 100;
                                    SD_Com.Open();
                                    Thread.Sleep(1);
                                    btn_Connect.ToolTipText = "Close";
                                    //btn_Connect.Image = Properties.Resources.Disconnect;
                                    toolStripComboBox1.Enabled = false;
                                    SD_Com_en = true;
                                    //Read_Thread();
                                    toolStripComboBox1.Text = SD_Com.PortName.ToString();
                                    //User_des.Write("User_Com", SD_Com.PortName.ToString());
                                    Console.Beep();
                                    break;
                                    
                                }
                                catch (Exception ex)
                                {
                                    MessageBox.Show(ex.Message.ToString(),"Error");
                                    Console.Beep();
                                    break;
                                }
                                
                            }
                            Thread.Sleep(1);
                        }
                    }
                    catch
                    {
                        MessageBox.Show("Check Connection!","Error");
                        toolStripComboBox1.Text = "Auto Search";
                        Console.Beep();
                        SD_Com.Close();
                        SD_Com = null;
                        btn_Connect.ToolTipText = "Open";
                        btn_Connect.Image = Properties.Resources.Connect1;
                        toolStripComboBox1.Enabled = true;
                    }
                }
               
           
                #region Manual
                if (toolStripComboBox1.Text != "")
                {
                    if (_num == -1)
                    {
                        MessageBox.Show( "Select Com-port!!","Error");
                    }
                    else
                    {
                        SD_Com = new SerialPort(toolStripComboBox1.Text,115200);
                        if (SD_Com.IsOpen == false)
                        {
                            try
                            {
                                toolStripComboBox1.Text = SD_Com.PortName.ToString();
                                SD_Com.ReadTimeout = 100;
                                SD_Com.Open();
                                //User_des.Write("User_Com", SD_Com.PortName.ToString());
                                btn_Connect.ToolTipText = "Close";
                                //btn_Connect.Image = Properties.Resources.Disconnect;
                                toolStripComboBox1.Enabled = false;
                                SD_Com_en = true;
                                //Read_Thread();
                            }
                            catch (Exception ex)
                            {
                                MessageBox.Show(ex.Message.ToString(),"Error");
                                toolStripComboBox1.Text = "Auto Search";
                                //User_des.Write("User_Com", "");
                                Console.Beep();
                            }
                        }
                    }
                }
                else
                {
                    MessageBox.Show("Select Port Name","Error");
                    Console.Beep();
                }
                #endregion*/
            }
            #endregion

            //###################################################################

            #region PORT Close
            else
            {
               

                btn_Connect.ToolTipText = "Open";
                btn_Connect.Image = Properties.Resources.Connect1;
                toolStripComboBox1.Enabled = true;
                SD_Com.Close();

                Form1 NewForm = new Form1();
                NewForm.Show();
                this.Dispose(false);
            }
            #endregion

        }

        private void Reset_btn_Click(object sender, EventArgs e)
        {

        }

    }
}
