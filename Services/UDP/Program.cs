using System;
using System.Device.Gpio;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Text;

class Program
{
    const int ButtonPin = 27;
    static DateTime _lastPress = DateTime.MinValue;
    static readonly TimeSpan DebounceTime = TimeSpan.FromMilliseconds(500);

    static void Main()
    {
        Console.WriteLine("C# GPIO service started");

        using var gpio = new GpioController();

        // Input mode only
        gpio.OpenPin(ButtonPin, PinMode.Input);

        gpio.RegisterCallbackForPinValueChangedEvent(
            ButtonPin,
            PinEventTypes.Falling,
            OnButtonPressed
        );

        Thread.Sleep(Timeout.Infinite);
    }

    static void OnButtonPressed(object sender, PinValueChangedEventArgs e)
    {
        var now = DateTime.UtcNow;

        if (now - _lastPress < DebounceTime)
            return; // ignore bounce

        _lastPress = now;

        Console.WriteLine("Button pressed");

        // Run the script async
        _ = RunScriptAsync();
    }

    static async Task RunScriptAsync()
    {
        try
        {
            var psi = new ProcessStartInfo
            {
                FileName = "/bin/bash",
                ArgumentList = { "/home/stage/defqon_ws/Defqon/MusicStart.sh" },
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardError = true
            };

            using var process = Process.Start(psi);

            if (process == null)
            {
                Console.WriteLine("Failed to start the script!");
                return;
            }

            // Read output for debugging
            string output = await process.StandardOutput.ReadToEndAsync();
            string error = await process.StandardError.ReadToEndAsync();

            await process.WaitForExitAsync();

            Console.WriteLine("Script output: " + output);
            if (!string.IsNullOrEmpty(error))
                Console.WriteLine("Script error: " + error);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error running script: {ex.Message}");
        }
    }

}
