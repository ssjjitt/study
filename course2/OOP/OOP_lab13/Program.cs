/*BinaryFormatter formatter = new BinaryFormatter();
           using (FileStream fs = new FileStream("circle.dat", FileMode.OpenOrCreate))
           {
               try
               {
                   formatter.Serialize(fs, sqr);
               }
               catch(SerializationException e)
               {
                   Console.WriteLine(e.Message);
                   throw;
               }
           }
           using (FileStream fs = new FileStream("circle.dat", FileMode.OpenOrCreate))
           {
               Square nsquare = (Square)formatter.Deserialize(fs);
               Console.WriteLine($"Square: {nsquare.ToString}");
           }*/

/*SoapFormatter formatter1 = new SoapFormatter();
 using (FileStream fs = new FileStream("circle1.dat", FileMode.OpenOrCreate, FileAccess.Write, FileShare.None))
 {
     try
     {
         formatter1.Serialize(fs, sqr);
     }
     catch (SerializationException e)
     {
         Console.WriteLine(e.Message);
         throw;
     }
 }
 using (FileStream fs = new FileStream("circle1.dat", FileMode.OpenOrCreate))
 {
     Square nsquare = (Square)formatter1.Deserialize(fs);
     Console.WriteLine($"Square: {nsquare.ToString}");
 }*/
using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
// using System.Runtime.Serialization.Formatters.Soap;
using System.Xml.Serialization;
using System.IO;
using System.Xml;
using System.Text;
using System.Threading.Tasks;
using System.Linq;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Text.Json;

namespace OOP_lab13
{
    class Program
    {
        private static void Main(string[] args)
        {
            Square sqr = new Square(1, 2, 2);
            Circle crc = new Circle(3, 1);
            GeometricFigure figure = new GeometricFigure();
            figure.Color = GeometricFigure.Colors.Red;
            Console.WriteLine("Сериализация/десериализация: ");
            // 1
            string pathJson = "../../../sqr.json";
            string pathXml = "../../../crc.xml";
            string pathJson2 = "../../../figure.json";
            string pathXml2 = "../../../figure.xml";

            string jsonSer = System.Text.Json.JsonSerializer.Serialize(sqr);
            File.WriteAllText(pathJson, jsonSer);
            string jsonDeser = File.ReadAllText(pathJson);
            Square deser = System.Text.Json.JsonSerializer.Deserialize<Square>(jsonDeser);
            Console.WriteLine("Площадь Square:" + deser.Area);

            XmlSerializer xmlSer = new XmlSerializer(typeof(Circle));
            using (FileStream fs = new FileStream(pathXml, FileMode.OpenOrCreate))
            {
                xmlSer.Serialize(fs, crc);
            }
            using (FileStream fs = new FileStream(pathXml, FileMode.Open))
            {
                Circle deser1 = xmlSer.Deserialize(fs) as Circle;
                Console.WriteLine("Площадь Circle:" + deser1.Area);
            }

            Console.WriteLine("Запрет сериализации одного из членов: ");

            XmlSerializer xmlSerializer = new XmlSerializer(typeof(GeometricFigure));
            using (FileStream fs = new FileStream(pathXml2, FileMode.OpenOrCreate))
            {
                xmlSerializer.Serialize(fs, figure);
            }
            using (FileStream fs = new FileStream(pathXml2, FileMode.Open))
            {
                GeometricFigure deser2 = xmlSerializer.Deserialize(fs) as GeometricFigure;
                Console.WriteLine("Цвет GeometricFigure:" + deser2.Color + " - разрешено");
            }

            string jsonSer2 = System.Text.Json.JsonSerializer.Serialize(figure);
            File.WriteAllText(pathJson2, jsonSer2);
            string jsonDeser2 = File.ReadAllText(pathJson2);
            GeometricFigure deser3 = System.Text.Json.JsonSerializer.Deserialize<GeometricFigure>(jsonDeser2);
            Console.WriteLine("Цвет GeometricFigure2:" + deser3.Color + " - запрещено");



            // 2
            List<Square> list = new List<Square>() {
                new Square { Area = 28 },
                new Square { Area = 44 },
                new Square { Area = 55 },
                new Square { Area = 13 }
            };
            string pathList = "../../../list.json";
            string jsonString = System.Text.Json.JsonSerializer.Serialize(list);
            File.WriteAllText(pathList, jsonString);
            string jsonString1 = File.ReadAllText(pathList);
            List<Square> deserializedObjects = System.Text.Json.JsonSerializer.Deserialize<List<Square>>(jsonString1);
            Console.WriteLine("Десериализация коллекции: ");
            foreach (var obj in deserializedObjects)
            {
                Console.WriteLine($"Площадь: {obj.Area}");
            }

            // 3
            Console.WriteLine("XPath: ");
            XmlDocument xDoc = new XmlDocument();
            xDoc.Load("../../../thirdTask.xml");
            XmlElement? xRoot = xDoc.DocumentElement;

            XmlNodeList? personNodes = xRoot?.SelectNodes("person");
            if (personNodes is not null)
            {
                foreach (XmlNode node in personNodes)
                    Console.WriteLine(node.SelectSingleNode("@name")?.Value);
            }

            XmlNode? tomNode = xRoot?.SelectSingleNode("person[@name='Tom']");
            Console.WriteLine(tomNode?.SelectSingleNode("@name")?.Value);

            XmlNodeList? companyNodes = xRoot?.SelectNodes("//person/company");
            if (companyNodes is not null)
            {
                foreach (XmlNode node in companyNodes)
                    Console.WriteLine(node.InnerText);
            }



            // 4 
            Console.WriteLine("Linq to Json");
            JObject jsonDoc = new JObject(
                new JProperty("databases",
                    new JArray(
                        new JObject(
                            new JProperty("name", "MySQL"),
                            new JProperty("type", "RDBMS")
                        ),
                        new JObject(
                            new JProperty("name", "MongoDB"),
                            new JProperty("type", "NoSQL")
                        ),
                        new JObject(
                            new JProperty("name", "Neo4j"),
                            new JProperty("type", "Graph DB")
                        )
                    )
                )
            );
            string filePath = "../../../databases.json";
            File.WriteAllText(filePath, jsonDoc.ToString());

            string jsonContent = File.ReadAllText(filePath);
            JObject jsonDocument = JObject.Parse(jsonContent);
            Console.WriteLine(jsonDocument.ToString());
            JArray databasesArray = (JArray)jsonDocument["databases"];
            foreach (JObject databaseObj in databasesArray)
            {
                string name = (string)databaseObj["name"];
                string type = (string)databaseObj["type"];
                Console.WriteLine($"name: {name}, type: {type}");
            }
            string databaseName = "MySQL";
            JObject mysqlDatabase = databasesArray.FirstOrDefault(db => (string)db["name"] == databaseName) as JObject;
            if (mysqlDatabase != null)
            {
                string type = (string)mysqlDatabase["type"];
                Console.WriteLine($"БД {databaseName} тип: {type}");
            }

            // Пример: Получение всех баз данных определенного типа
            string targetType = "NoSQL";
            List<JObject> targetDatabases = databasesArray
                .Where(db => (string)db["type"] == targetType)
                .Select(db => db as JObject)
                .ToList();

            Console.Write($"БД типа {targetType}: ");
            foreach (JObject databaseObj in targetDatabases)
            {
                string name = (string)databaseObj["name"];
                Console.WriteLine(name);
            }
        }
    }

    class Database
    {
        public string Name { get; set; }
        public string Type { get; set; }
    }

}
    