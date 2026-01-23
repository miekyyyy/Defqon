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
        int i = Random.Shared.Next(1112, 12000);

        UdpClient udp = new UdpClient(i);
        IPEndPoint serverEP = new IPEndPoint(IPAddress.Parse("192.168.64.185"), 1111);
        string message = "Start";
        byte[] StartMessage = Encoding.UTF8.GetBytes(message);

        udp.Send(StartMessage, StartMessage.Length, serverEP);

        udp.Close();
    }

}