using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using RFID;

namespace WebApplication1
{
    public partial class _Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            byte[] arrBuffer = new byte[64];
            if (RFID.SWNetApi.SWNet_OpenDevice("192.168.1.250", 60000))
            {
                if (RFID.SWNetApi.SWNet_GetDeviceSystemInfo(0xFF, arrBuffer) == true)
                {
                    string str = "", str1 = "";
                    str = "SN:";
                    for (int i = 0; i < 7; i++)
                    {
                        str1 = String.Format("{0:X2}", arrBuffer[2 + i]);
                        str = str + str1;
                    }
                    str = str + " ";
                    TextBox1.Text = str;
                }
            }
            else
            {
                TextBox1.Text="Failed";
            }
        }
    }
}
