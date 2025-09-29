using System;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace lab1_task4
{
    public partial class Form1 : Form
    {
        private readonly HttpClient client = new HttpClient();

        public Form1()
        {
            InitializeComponent();
        }

        public class Calc
        {
            public int X { get; set; }
            public int Y { get; set; }
        }

        private async void btnAdd_Click(object sender, EventArgs e)
        {
            try
            {
                int x = Convert.ToInt32(txtX.Text);
                int y = Convert.ToInt32(txtY.Text);
                
                var requestData = new Calc { X = x, Y = y };
                
                var json = JsonConvert.SerializeObject(requestData);
                
                var content = new StringContent(json, Encoding.UTF8, "application/json");
                
                var response = await client.PostAsync("https://localhost:7160/gdv/calc", content);
                if (response.IsSuccessStatusCode)
                {
                    var result = await response.Content.ReadAsStringAsync();
                    lblResult.Text = result;
                }
                else
                {
                    lblResult.Text = $"Error: {response.StatusCode} - {response.ReasonPhrase}";
                }
            }
            catch (Exception ex)
            {
                lblResult.Text = $"error: {ex.Message}\n{ex.StackTrace}";
            }
        }
    }
}
