using System;
using System.Collections.Generic;
using System.Text.Json;

namespace ExamPizdaZalypaXo4yAvtomatRatatatata
{
    class User
    {
        private string email;
        private string password;
        private string status;
      
        public string newStatus
        {
            get
            {
                return status;
            }
            set
            {
                if (value == "signin")
                {
                    status = value;
                }
                else if(value == "signout")
                {
                    status = value;
                }
                else 
                {
                    status = "хуйня твой статус дебил блять";
                }
            }
        }

        public User()
        {
            this.email = "email empty";
            this.password = "pass empty";
            this.newStatus = "signout";
        }

        public User(string em, string pass, string status)
        {
            this.email = em;
            this.password = pass;
            this.newStatus = status;
        }

        public override string ToString()
        {
            return "\nemail: " + email + "\npassword: " + password + "\nstatus: " + status;
        }
     
        public override bool Equals(object? obj)
        {
            if (obj is User)
            {
                return true;
            }
            return false;
        }

        public override int GetHashCode()
        {
            return email.GetHashCode() + password.GetHashCode();
        }

        public string CompareTo(string str, int num) {
            string res = "priv";
            for (int i = 0; i < num; i++)
            {
                res = res + i;
            }
            return res;
        }

    }

    class WebNet
    {
        private LinkedList<User> users = new LinkedList<User>();
        public WebNet() { }
        public int AddUser(User user) 
        {
            users.AddLast(user);
            return users.Count + 1;
        }
        public int RemoveUser()
        {
            users.RemoveLast();
            return users.Count - 1;
        }
        public LinkedList<User> GetUsers()
        {
            return users;
        }
    }

    class Program
    {
        static void Main()
        {
            User user = new User();
            Console.WriteLine(user.ToString());
            User user1 = new User("Tom", "12345678", "13213"); 
            Console.WriteLine("\nToString" + user1.ToString());
            Console.WriteLine("\nEquals: " + user.Equals(user1));
            Console.WriteLine("\nGetHashCode: " + user.GetHashCode());
            Console.WriteLine("\nCompare: " + user1.CompareTo("et", 5)); // хуйня, но сойдет
            WebNet github = new WebNet();
            github.AddUser(user);
            github.AddUser(user1);
            github.AddUser(new User());
            LinkedList<User> users = github.GetUsers();
            Console.WriteLine("\n\nUserы");
            foreach (User us in users)
            {
                Console.WriteLine(us.ToString());
            } 
            Console.WriteLine("\nКолво = " + users.Count());
            string json = JsonSerializer.Serialize(users);
            string path = "../../../users.json";
            File.WriteAllText(path, json);
        }
    }
}