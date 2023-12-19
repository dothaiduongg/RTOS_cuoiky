using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Button;

namespace DemoWindowsForm
{
    public partial class Form1 : Form
    {

        SerialPort serialPort;

        double temperature = 0, humidity = 0;
        //double time = 0, day = 0, dow = 0;
        bool updateData  = false;
        public Form1()
        {
            InitializeComponent();
            disenableControl();
            String[] Baudrate = { "1200", "2400", "4800", "9600", "19200", "115200" };
            cboBaudrate.Items.AddRange(Baudrate);
            Control.CheckForIllegalCrossThreadCalls = false;
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            cboComport.DataSource = SerialPort.GetPortNames();
            cboBaudrate.Text = "9600";
            //button3.Enabled = false;
            
        }

        private void backgroundWorker2_DoWork(object sender, DoWorkEventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

            if (!serCOM.IsOpen)
            {
            string dulieu = sendtext.Text;
            serCOM.Write("#text" + dulieu + "#\n");
            }


        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }
        private void button2_Click(object sender, EventArgs e)
        {
            if (!serCOM.IsOpen)
            {

                buttonConnect.Text = "Disconnected";
                serCOM.PortName = cboComport.Text;
                serCOM.BaudRate = Convert.ToInt32("9600");
                serCOM.Open();
                button3.Enabled = true;
                enableControl();
                MessageBox.Show("Success");
            }
            else
            {
                buttonConnect.Text = "Connected";
                serCOM.Close();
                disenableControl();
                MessageBox.Show("no success");
            }


            //try
            //{
            //    serCOM.PortName = cboComport.Text;
            //    serCOM.BaudRate = Convert.ToInt32("9600");
            //    serCOM.Open();


            //}
            //catch (Exception error)
            //{
            //    MessageBox.Show(error.Message);
            //}
        }


        private void button3_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void cboComport_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void cboBaudrate_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void enableControl()
        {
            label2.Enabled = true;
            label3.Enabled = true;
            label4.Enabled = true;
            label5.Enabled = true;
            label6.Enabled = true;
            label7.Enabled = true;
            //label8.Enabled = true;
            //label9.Enabled = true;
            sendtext.Enabled = true;
            comboBox1.Enabled = true;
            button1.Enabled = true;
            button2.Enabled = true;
            groupBox1.Enabled = true;
            //.Enabled = true;
        }

        private void disenableControl()
        {
            label2.Enabled = false;
            label3.Enabled = false;
            label4.Enabled = false;
            label5.Enabled = false;
            label6.Enabled = false;
            label7.Enabled = false;
            //label8.Enabled = false;
            //label9.Enabled = false;
            sendtext.Enabled = false;
            comboBox1.Enabled = false;
            button1.Enabled = false;
            button2.Enabled = false;
            groupBox1.Enabled = false;
            //groupBox2.Enabled = false;
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            sendtext.Text = "";
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }



        private void serCOM_receive(object sender, SerialDataReceivedEventArgs e)
        {
            string dataIn = serCOM.ReadTo("\n");
            Data_Parsing(dataIn);
            this.BeginInvoke(new EventHandler(Show_Data));
        }

        private void Data_Parsing(string data)
        {
            sbyte index0f_startDataCharacter = (sbyte)data.IndexOf("@");
            sbyte index0fA = (sbyte)data.IndexOf("A");      //day of week
            sbyte index0fB = (sbyte)data.IndexOf("B");      //day 
            //sbyte index0fC = (sbyte)data.IndexOf("C");      //temperature
            //sbyte index0fD = (sbyte)data.IndexOf("D");      //humidity
            //sbyte index0fE = (sbyte)data.IndexOf("E");      

            // if character "A", "B" and "@" exxist in the data Package
            if (index0fA != -1 && index0fB != -1 /*&& index0fC != -1 && index0fD != -1 && index0fE != -1*/ && index0f_startDataCharacter != -1 )
            {
                try
                {
                    //string str_time = data.Substring(index0f_startDataCharacter + 1,
                    //    (index0fA - index0f_startDataCharacter) - 1);

                    //string str_dow = data.Substring(index0fA + 1, (index0fB - index0fA) - 1);
                    //string str_day = data.Substring(index0fB + 1, (index0fC - index0fB) - 1);
                    //string str_temprature = data.Substring(index0fC + 1, (index0fD - index0fC) - 1);
                    ////string str_humidity = data.Substring(index0fD + 1, (index0fE - index0fD) - 1);
                    //string str_dow = data.Substring(index0f_startDataCharacter + 1,
                    //    (index0fA - index0f_startDataCharacter) - 1);

                    //string str_day = data.Substring(index0fA + 1, (index0fB - index0fA) - 1);
                    string str_temprature = data.Substring(index0f_startDataCharacter + 1,
                            (index0fA - index0f_startDataCharacter) - 1);
                    string str_humidity = data.Substring(index0fA + 1, (index0fB - index0fA) - 1);
                    //string str_humidity = data.Substring(index0fD + 1, (index0fE - index0fD) - 1);

                    //time = Convert.ToDouble(str_time);
                    //dow = Convert.ToDouble(str_dow);
                    //day = Convert.ToDouble(str_day);
                    temperature = Convert.ToDouble(str_temprature);
                    humidity = Convert.ToDouble(str_humidity);



                    updateData = true;
                }
                catch (Exception)
                {

                }
            }
            else
            {
                updateData = false;
            }
        }
        private void Show_Data(object sender, EventArgs e)
        {
            if (updateData == true) {

                
                //label6.Text = String.Format("Thời gian: {0}", time.ToString());
                //label7.Text = String.Format("Ngày: {0}, {0}", dow.ToString(), day.ToString());

                label4.Text = String.Format("Nhiệt độ: {0}°C", temperature.ToString());
                label5.Text = String.Format("Độ ẩm: {0}%RH", humidity.ToString());
            }
        }
    }
}
