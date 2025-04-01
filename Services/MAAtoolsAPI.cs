using System;
using MAAtools.API;
namespace MAAtools.Services;
    public class MAAtoolsAPI : IMAAToolsAPI{
        public void Start(){
            Console.WriteLine("Starting MAAtools API1.0");
        }
        public void Stop(){
            Console.WriteLine("Stopping MAAtools API");
        }
    }

    public class MAAtoolsAPI2 : IMAAToolsAPI{
        public string name{
            get=> "MAAtools API2.0";
            set{
                Console.WriteLine("Name cannot be changed");
            }
        }
        public void Start(){
            Console.WriteLine("Starting MAAtools API2.0");
        }
        public void Stop(){
            Console.WriteLine("Stopping MAAtools API2");
        }
    }


    
