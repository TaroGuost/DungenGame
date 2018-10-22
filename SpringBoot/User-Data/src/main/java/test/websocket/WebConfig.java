package test.websocket;

import org.springframework.context.annotation.Configuration;
import org.springframework.messaging.simp.config.MessageBrokerRegistry;
import org.springframework.web.socket.config.annotation.EnableWebSocketMessageBroker;
import org.springframework.web.socket.config.annotation.StompEndpointRegistry;
import org.springframework.web.socket.config.annotation.WebSocketMessageBrokerConfigurer;


@Configuration
@EnableWebSocketMessageBroker
public class WebConfig implements WebSocketMessageBrokerConfigurer{

	@Override
	public void registerStompEndpoints(StompEndpointRegistry config) {
		// TODO Auto-generated method stub
		config.addEndpoint("/Uweb").withSockJS();
	}

	@Override
	public void configureMessageBroker(MessageBrokerRegistry config) {
		// TODO Auto-generated method stub
		config.enableSimpleBroker("/topic");
		config.setApplicationDestinationPrefixes("/app");
	}
	
	
	

}
