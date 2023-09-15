package main;


import com.google.api.gax.core.FixedCredentialsProvider;
import com.google.auth.oauth2.GoogleCredentials;
import com.google.cloud.pubsub.v1.AckReplyConsumer;
import com.google.cloud.pubsub.v1.MessageReceiver;
import com.google.cloud.pubsub.v1.Subscriber;
import com.google.pubsub.v1.ProjectSubscriptionName;
import com.google.pubsub.v1.PubsubMessage;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class AdsSubscriber extends Thread{

    public static final String TEXT_GREEN = "\u001B[32m";
    public static final String TEXT_BLUE = "\u001B[34m";
    public static final String TEXT_RED = "\u001B[31m";
    public static final String TEXT_RESET = "\u001B[0m";

    public void main(String... args) throws Exception {
        String projectId = "room-rent-374417";
        String subscriptionId = "clients";

        subscribeAsyncExample(projectId, subscriptionId);
    }

    public void run() {
        try {
            this.main();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static void subscribeAsyncExample(String projectId, String subscriptionId) {
        ProjectSubscriptionName subscriptionName = ProjectSubscriptionName.of(projectId, subscriptionId);

        // Instantiate an asynchronous message receiver.
        MessageReceiver receiver = (PubsubMessage message, AckReplyConsumer consumer) -> {
            // Handle incoming message, then ack the received message.
            System.out.println("\n[ " + TEXT_GREEN + "Aviso: " + message.getData().toStringUtf8() + TEXT_RESET + " ]\n" );
            consumer.ack();
        };

        Subscriber subscriber = null;
        try {
            GoogleCredentials credentials = GoogleCredentials.fromStream( new FileInputStream("src/main/java/main/room-rent-374417-70043a788166.json"));
            subscriber = Subscriber.newBuilder(subscriptionName, receiver).setCredentialsProvider(FixedCredentialsProvider.create(credentials)).build();
            // Start the subscriber.
            subscriber.startAsync().awaitRunning();
        }
        catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}