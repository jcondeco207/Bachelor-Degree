package sd.rest;

import com.google.api.gax.core.FixedCredentialsProvider;
import com.google.auth.oauth2.GoogleCredentials;
import com.google.cloud.pubsub.v1.Publisher;
import com.google.protobuf.ByteString;
import com.google.pubsub.v1.ProjectTopicName;
import com.google.pubsub.v1.PubsubMessage;
import java.io.FileInputStream;


public class AdPublisher {

  public static void publish(String msg) throws Exception {
    // Your Google Cloud Platform project ID
    String projectId = "room-rent-374417";

    // The name of the topic to which messages will be sent
    String topicId = "Ads";

    ProjectTopicName topicName = ProjectTopicName.of(projectId, topicId);
    Publisher publisher = null;
    try {

      GoogleCredentials credentials = GoogleCredentials.fromStream( new FileInputStream("src/main/java/sd/rest/room-rent-374417-bbf740e1f892.json"));
      // Create a publisher instance with default settings bound to the topic
      publisher = Publisher.newBuilder(topicName).setCredentialsProvider(FixedCredentialsProvider.create(credentials)).build();

      // Convert the message to bytes
      byte[] data = msg.getBytes("UTF-8");
      // Create a pubsub message
      PubsubMessage pubsubMessage = PubsubMessage.newBuilder().setData(ByteString.copyFrom(data)).build();
      // Schedule the message for publishing
      publisher.publish(pubsubMessage);
      System.out.println(msg);
    }
    finally {
      if (publisher != null) {
        // When finished with the publisher, shutdown to free up resources
        publisher.shutdown();
      }
    }
  }

}
