package Client;

import  net.thegreshams.firebase4j.error.FirebaseException;
import net.thegreshams.firebase4j.service.Firebase;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class frm_Control extends JFrame {
    private JButton btnOn;
    private JButton btnOff;
    private JPanel mainPanel;
    private JTextArea txtArea;
    private JCheckBox autoCheckBox;
    private JTextArea txtArea1;
    private JButton btnAuto;
    private JComboBox cmbValue;

    public frm_Control(GraphicsConfiguration gc) {
        super(gc);
    }

    public frm_Control() {
        setContentPane(mainPanel);
        setTitle("Welcome");
        setSize(500, 400);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        txtArea1.setEditable(false);
        txtArea.setEditable(false);
        setVisible(true);
        for (int i = 100; i <= 1001; i += 100) {
            cmbValue.addItem(i);
        }

        //get data from firebase real-time database then set text to text area
        new Thread(new Runnable() {
            @Override
            public void run() {
                Firebase firebase = null;
                try {
                    firebase = new Firebase("https://control-pump-water-default-rtdb.asia-southeast1.firebasedatabase.app");
                } catch (FirebaseException e) {
                    throw new RuntimeException(e);
                }
                try {
                    while (true) {
                        String value = firebase.get("/").getBody().get("value").toString();
                        String timestamp = firebase.get("/").getBody().get("timestamp").toString();
                        txtArea1.setText(value + "\n" + timestamp + "\n");

                        Thread.sleep(1000);
                    }
                } catch (IOException ex) {
                    Logger.getLogger(frm_Control.class.getName()).log(Level.SEVERE, null, ex);
                } catch (FirebaseException | InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }).start();

        btnOn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    String data = "1";
                    DatagramSocket clientSocket = new DatagramSocket();
                    byte[] sendData = data.getBytes();
                    DatagramPacket packetSend = new DatagramPacket(sendData, sendData.length, InetAddress.getByName("localhost"), 8888);
                    clientSocket.send(packetSend);
                    clientSocket.close();
                } catch (SocketException ex) {
                    throw new RuntimeException(ex);
                } catch (IOException ex) {
                    Logger.getLogger(frm_Control.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
        btnOff.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    String data = "2";
                    DatagramSocket clientSocket = new DatagramSocket();
                    byte[] sendData = data.getBytes();
                    DatagramPacket packetSend = new DatagramPacket(sendData, sendData.length, InetAddress.getByName("localhost"), 8888);
                    clientSocket.send(packetSend);
                    clientSocket.close();
                } catch (SocketException ex) {
                    throw new RuntimeException(ex);
                } catch (IOException ex) {
                    Logger.getLogger(frm_Control.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
        autoCheckBox.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (autoCheckBox.isSelected() == true) {
                    btnOn.setEnabled(false);
                    btnOff.setEnabled(false);
                    btnAuto.setEnabled(true);
                    txtArea.setEnabled(true);
                    try {
                        String data = "3";
                        DatagramSocket clientSocket = new DatagramSocket();
                        byte[] sendData = data.getBytes();
                        DatagramPacket packetSend = new DatagramPacket(sendData, sendData.length, InetAddress.getByName("localhost"), 8888);
                        clientSocket.send(packetSend);
                        clientSocket.close();
                    } catch (SocketException ex) {
                        throw new RuntimeException(ex);
                    } catch (IOException ex) {
                        Logger.getLogger(frm_Control.class.getName()).log(Level.SEVERE, null, ex);
                    }

                } else if (autoCheckBox.isSelected() == false) {
                    btnOn.setEnabled(true);
                    btnOff.setEnabled(true);
                    btnAuto.setEnabled(false);
                    txtArea.setEnabled(true);
                    try {
                        String data = "2";
                        DatagramSocket clientSocket = new DatagramSocket();
                        byte[] sendData = data.getBytes();
                        DatagramPacket packetSend = new DatagramPacket(sendData, sendData.length, InetAddress.getByName("localhost"), 8888);
                        clientSocket.send(packetSend);
                        clientSocket.close();
                    } catch (SocketException ex) {
                        throw new RuntimeException(ex);
                    } catch (IOException ex) {
                        Logger.getLogger(frm_Control.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });
        btnAuto.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    String data = cmbValue.getSelectedItem().toString();
                    DatagramSocket clientSocket = new DatagramSocket();
                    byte[] sendData = data.getBytes();
                    DatagramPacket packetSend = new DatagramPacket(sendData, sendData.length, InetAddress.getByName("localhost"), 8888);
                    clientSocket.send(packetSend);
                    clientSocket.close();
                } catch (SocketException ex) {
                    throw new RuntimeException(ex);
                } catch (IOException ex) {
                    Logger.getLogger(frm_Control.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
    }

    public static void main(String[] args) {
        frm_Control frmControl = new frm_Control();
    }
}
