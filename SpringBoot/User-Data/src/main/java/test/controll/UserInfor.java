package test.controll;

import javax.persistence.Entity;
import javax.persistence.Id;

@Entity
public class UserInfor {

	@Id
	private int id;
	private String username;
	private String password;
	private String Name;
	private int Age;
	
	public UserInfor() {
	
	}
	
	

	public UserInfor(int id, String username, String password, String name, int age) {
		this.id = id;
		this.username = username;
		this.password = password;
		Name = name;
		Age = age;
	}
	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getName() {
		return Name;
	}
	public void setName(String name) {
		Name = name;
	}
	public int getAge() {
		return Age;
	}
	public void setAge(int age) {
		Age = age;
	}
	
	
	
	
	
}
