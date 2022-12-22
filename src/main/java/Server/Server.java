package Server;

import java.net.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

import Client.*;
import net.thegreshams.firebase4j.error.FirebaseException;
import net.thegreshams.firebase4j.error.JacksonUtilityException;
import net.thegreshams.firebase4j.service.Firebase;

public class Server {
    public static void main(String[] args) throws FirebaseException, JacksonUtilityException {

//connect to real-time firebase database
        Firebase firebase = new Firebase("https://control-pump-water-default-rtdb.asia-southeast1.firebasedatabase.app");
        System.out.println("Connected to Firebase");
        try {
            DatagramSocket severSocket = new DatagramSocket(8888);
            byte[] receiveData = new byte[1024];
            byte[] sendData = new byte[1024];

            while (true) {
                DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                receivePacket.setLength(receiveData.length);
                severSocket.receive(receivePacket);
                String data = new String(receivePacket.getData(), 0, receivePacket.getLength());
                System.out.println(data);
//                String data1 = data.replace("\0", "");
//                String data2 = data1.replace("f", "");
                InetAddress IPAddress = receivePacket.getAddress();
                String ipReceive = IPAddress.toString();
                int port = receivePacket.getPort();
                sendData = data.getBytes();
                byte[] ipAddr = new byte[]{(byte) 192, (byte) 168, (byte) 1, (byte) 6};
                String ipText = "/192.168.1.6";
                boolean check = ipReceive.equals(ipText);
//                System.out.println(check);
                if (IPAddress.equals(ipText)) {
                    DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
                    severSocket.send(sendPacket);
                } else {
                    DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, InetAddress.getByAddress(ipAddr), 6767);
                    severSocket.send(sendPacket);
                    //send to firebase real-time database
                    var dataMap = new HashMap<String, Object>();

//                    if (!data.contains("[a-zA-Z]+") && data.length() > 2) {
//
//                    }
                    dataMap.put("value", data);
                    dataMap.put("timestamp", new SimpleDateFormat("dd/MM/yyyy HH:mm:ss").format(Calendar.getInstance().getTime()));
                    firebase.put("/", dataMap);
                }
            }
        } catch (IOException ex) {
            Logger.getLogger(frm_Control.class.getName()).log(Level.SEVERE, null, ex);
        }

    }
}
