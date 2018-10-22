package test.controll;

import java.util.List;
import java.util.Optional;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;

public interface User_data extends CrudRepository<UserInfor , Integer> {

	@Query("SELECT AVG(u.Age) from UserInfor u")
	int AveageAge();
	
	@Query(value = "SELECT max(u.Age) from user_infor u ",nativeQuery = true)
	int maxAge();
	
	@Query(value = "SELECT * FROM user_infor u WHERE u.Name = ?1", 
			  nativeQuery = true)
	List<UserInfor> getnameV(String name);
	
	@Query(value = "SELECT * FROM user_infor u WHERE u.Age =  ?1" , nativeQuery = true)
	List<UserInfor> getSameAge(int age);

}
