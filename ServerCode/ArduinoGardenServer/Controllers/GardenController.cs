using ArduinoGardenServer.Filters;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web;
using System.Web.Http;

namespace ArduinoGardenServer.Controllers
{
    public class GardenController : ApiController
    {
        public class Point
        {
            public int x { get; set; }
            public int y { get; set; }
        }

        private string GetPath(string fileName)
        {
            if (HttpContext.Current.Request.IsLocal)
                return HttpContext.Current.Server.MapPath("/Data/" + fileName);
            else
                return HttpContext.Current.Server.MapPath("/ArduinoGarden/Data/" + fileName);
        }

        #region Light
        [Route("api/Garden/SetValue/{value}"), HttpGet]
        public string SetValue(int value)
        {
            if (!(value == 0 || value == 1))
                return "NOT OK";

            if (File.ReadAllText(GetPath("LightData.txt")).Split('\n').Length > 200)
                File.WriteAllLines(GetPath("LightData.txt"), File.ReadAllLines(GetPath("LightData.txt")).Skip(100));

            File.AppendAllText(GetPath("LightData.txt"), DateTime.Now.ToString() + ";" + value.ToString() + "\n");

            return "OK";
        }

        [Route("api/Garden/GetValue"), HttpGet]
        [BasicAuthentication]
        public string GetValue()
        {
            string lines = File.ReadAllText(GetPath("LightData.txt"));

            return lines.Split('\n').Reverse().Skip(1).Take(1).FirstOrDefault().Split(';')[1];
        }

        [Route("api/Garden/LightData"), HttpGet]
        public string ImageData()
        {
            var lines = File.ReadAllText(GetPath("LightData.txt")).Split('\n');

            var points = new List<Point>();

            for (int i = 0; i < lines.Length - 1; i++)
            {
                var line = lines[i].Split(';');
                var date = DateTime.Parse(line[0]);

                var point = new Point()
                {
                    x = Convert.ToInt32(date.ToUniversalTime().Subtract(new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc)).TotalSeconds),
                    y = Convert.ToInt32(line[1])
                };

                points.Add(point);
            }

            return System.Web.Helpers.Json.Encode(points);
        }
        #endregion

        #region Moisture
        [Route("api/Garden/AddMoistureValue/{value}"), HttpGet]
        [BasicAuthentication]
        public string AddMoistureValue(int value)
        {
            if (value < 0 || value > 100)
                return "NOT OK";

            File.AppendAllText(GetPath("MoistureData.txt"), DateTime.Now.ToString() + ";" +  value.ToString() + "\n");

            return "OK";
        }

        [Route("api/Garden/MoistureData"), HttpGet]
        public string MoistureData()
        {
            var lines = File.ReadAllText(GetPath("MoistureData.txt")).Split('\n');

            var points = new List<Point>();

            for (int i = 0; i < lines.Length - 1; i++)
            {
                var line = lines[i].Split(';');
                var date = DateTime.Parse(line[0]);

                var point = new Point() {
                    x = Convert.ToInt32(date.ToUniversalTime().Subtract(new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc)).TotalMinutes),
                    y = Convert.ToInt32(line[1])
                };

                points.Add(point);
            }

            return System.Web.Helpers.Json.Encode(points);
        }
        #endregion
    }
}
