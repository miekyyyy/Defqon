namespace UDPClient;

using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

class Client
{
    public static void SendStartMessage()
    {
        try
        {
            int i = Random.Shared.Next(1112, 12000);

            using var udp = new UdpClient(i);

            string serverIp = Environment.GetEnvironmentVariable("DEFQON_SERVER_IP");

            if (string.IsNullOrEmpty(serverIp))
            {
                Console.WriteLine("ERROR: DEFQON_SERVER_IP not set!");
                return;
            }

            Console.WriteLine($"Sending UDP to {serverIp}:1111");

            IPEndPoint serverEP = new IPEndPoint(IPAddress.Parse(serverIp), 1111);

            string message = "Start";
            byte[] data = Encoding.UTF8.GetBytes(message);

            udp.Send(data, data.Length, serverEP);

            Console.WriteLine("UDP packet sent successfully");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"UDP send failed: {ex}");
        }
    }

}