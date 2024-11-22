import java.net.*;

public class UDPClient {
    public static void main(String[] args) {
        String serverAddress = "127.0.0.1";
        int port = 8080;
        String message = "Hello from UDP Client";
        
        try (DatagramSocket socket = new DatagramSocket()) {
            byte[] buffer = message.getBytes();
            
            InetAddress serverIP = InetAddress.getByName(serverAddress);
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, serverIP, port);
            socket.send(packet);
            
            byte[] responseBuffer = new byte[1024];
            DatagramPacket responsePacket = new DatagramPacket(responseBuffer, responseBuffer.length);
            socket.receive(responsePacket);
            
            String response = new String(responsePacket.getData(), 0, responsePacket.getLength());
            System.out.println("Message from server: " + response);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}
