package test.controll;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.ArrayList;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class Server {
	
	@Autowired
	private User_data data;
	
	
	
	
	public List<UserInfor> show()
	{
		List<UserInfor> temp = new ArrayList<>();
		data.findAll().forEach(temp::add);
		return temp;
		
	}
	
	public Optional<UserInfor> Find(int username)
	{
		
		return data.findById(username);
	}
	
	public void addUser(UserInfor user)
	{
		data.save(user);
	}

	public void Delete(int id) {
		data.deleteById(id);
		}
	
	public int AveAge()
	{
		return data.AveageAge();
	}
	
	public int getMaxAge()
	{
		return data.maxAge();
	}
	
	public List<UserInfor> getNameV(String name)
	{
		return data.getnameV(name);
	}
	
	public List<UserInfor> SameAge(int Age)
	{
		return data.getSameAge(Age);
	}

}








