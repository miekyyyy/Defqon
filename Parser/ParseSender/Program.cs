using System;
using System.IO;
using System.Linq;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Diagnostics;
using System.IO.Ports;
using System.Threading;

class Program
{
    // Event classes
    class Event
    {
        public string type { get; set; }
        public int targetId { get; set; }
        public string? lightEffectType { get; set; } // nullable
        public bool? inverted { get; set; } // nullable
        public Color? color { get; set; }          // nullable
        public float duration { get; set; }
        public float time { get; set; }
    }

    class Color
    {
        public float r { get; set; }
        public float g { get; set; }
        public float b { get; set; }
        public float a { get; set; }
    }

    class Root
    {
        [JsonPropertyName("$values")]
        public Event[]? Values { get; set; }       // nullable
    }

    // Main program
    static void Main()
    {
        try
        {
            // Read JSON
            string json = File.ReadAllText("myData.json");
            var root = JsonSerializer.Deserialize<Root>(json);

            if (root?.Values == null || root.Values.Length == 0)
            {
                Console.WriteLine("No events found in JSON.");
                return;
            }

            // Sort events by time
            var events = root.Values.OrderBy(e => e.time).ToArray();

            // Open serial port
            using var serial = new SerialPort("/dev/ttyACM0", 115200);
            serial.Open();
            Console.WriteLine("Serial port opened. Starting event playback");

            // Start stopwatch
            var stopwatch = Stopwatch.StartNew();

            // Send events at the scheduled time
            foreach (var evt in events)
            {
                // Wait until event.time is reached
                while (stopwatch.Elapsed.TotalSeconds < evt.time)
                    Thread.Sleep(1); // sleep 1 ms to avoid busy waiting

                // Build string 
                string toSend;
                if (evt.type == "Light")
                {
                    toSend =
                        $"{evt.type},{evt.targetId},{evt.lightEffectType},{(evt.inverted == true ? "1" : "0")}," +
                        $"{evt.color?.r ?? 0},{evt.color?.g ?? 0},{evt.color?.b ?? 0},{evt.color?.a ?? 0}," +
                        $"{evt.duration}\n";
                }
                else if (evt.type == "Smoke")
                {
                    toSend =
                        $"{evt.type},{evt.targetId},{evt.duration}\n";
                }
                else
                {
                    continue; // unknown event type
                }

                // Send to ESP32
                serial.Write(toSend);

                // Optional: print to console for debugging
                Console.WriteLine($"[{stopwatch.Elapsed.TotalSeconds:F3}s] Sent: {toSend.Trim()}");
            }

            Console.WriteLine("All events sent!");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Error: " + ex.Message);
        }
    }
}