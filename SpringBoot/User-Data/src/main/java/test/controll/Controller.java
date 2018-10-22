package test.controll;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class Controller {

	
	
	private List<UserInfor> users = new ArrayList<>(Arrays.asList( new UserInfor(14,"guost", "qwe", "xiuyuan" ,21),
			new UserInfor(11,"asdf", "qwe", "Kane" ,21),
			new UserInfor(12,"guo", "qwe", "fk" ,21),
			new UserInfor(13,"steven", "qwe", "xwww" ,21)
			
			));
	
	
	@Autowired
	private Server Userver;
	
	
	@RequestMapping("/user")
	public List<UserInfor> call()
	{
		return Userver.show();	
	}
	
	@RequestMapping("/user/{id}")
	public Optional<UserInfor> Find(@PathVariable int id)
	{
		return Userver.Find(id);
	}
	
	@RequestMapping("/user/delete/{id}")
	public String Delete(@PathVariable int id)
	{
		Userver.Delete(id);
		return "Delete Successfully";
		
	}
	
	@RequestMapping(method=RequestMethod.POST , value = "/user")
	public void Add(@RequestBody UserInfor user)
	{
		Userver.addUser(user);
	}
	
	@RequestMapping("/user/search/get_{name}")
	public List<UserInfor> name(@PathVariable String name)
	{
		return Userver.getNameV(name);
	}
	
	@RequestMapping("/user/Ave")
	public int getAveAge()
	{
		return Userver.AveAge();
	}
	
	@RequestMapping("/user/Max")
	public int getMaxAge()
	{
		return Userver.getMaxAge();
	}
	
	@RequestMapping("/user/search/age_{age}")
	public List<UserInfor> getAges(@PathVariable int age)
	{
		return Userver.SameAge(age);
	}
	
	@MessageMapping("/check")
	@SendTo("/topic/greet")
	public String showUsers(UserInfor user)
	{
		Userver.addUser(user);
		return user.getName();
	}
	
}
