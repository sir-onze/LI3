package engine;

import java.util.ArrayList;

public class User implements Comparable<User> {
	
	private long id;
	private String name, s_bio;
	private int reputation, n_posts;
	private ArrayList<Post> posts;
	
	/* Params Constructor */
	public User(long id, int reputation, String name, String s_bio, int n_posts) {
		this.id = id;
		this.n_posts = n_posts;
		this.name = name;
		this.s_bio = s_bio;
		this.reputation = reputation;
		this.posts = new ArrayList<Post>();
	}
	/* Copy Constructor */
	public User(User u) {
		this.id = u.get_id();
		this.n_posts = u.get_n_posts();
		this.name = u.get_name();
		this.s_bio = u.get_s_bio();
		this.reputation = u.get_reputation();
		this.posts = u.get_posts();
	}
	
	/* Getters */
	public long get_id() { return this.id; }
	public int get_n_posts() { return this.n_posts; }
	public String get_name() { return this.name; }
	public String get_s_bio() { return this.s_bio; }
	public int get_reputation() { return this.reputation; }
	public ArrayList<Post> get_posts(){ return this.posts; }
	/* Setters */
	public void set_id(long id) { this.id = id; }
	public void set_n_posts() { this.n_posts++; }
	public void set_name(String name) { this.name = name; }
	public void set_s_bio(String s_bio) { this.s_bio = s_bio; }
	public void set_reputation(int reputation) { this.reputation = reputation; }
	public void set_posts(ArrayList<Post> posts) { this.posts = posts; }
	
	/* Methods */
	public void add_post(Post p) { this.posts.add(p); }
	
	/* toString */
	@Override
	public String toString() {
		return "User [id=" + id + ", n_posts=" + n_posts + ", name=" + name
				+ ", s_bio=" + s_bio + ", reputation="+ reputation + "]";
	}
	/* equals */
	@Override
	public boolean equals(Object object) {
		if (this == object) return true;
		if (object == null || getClass() != object.getClass()) return false;
		if (!super.equals(object)) return false;
		User user = (User) object;
		return id == user.id &&
				n_posts == user.n_posts &&
				reputation == user.reputation &&
				java.util.Objects.equals(name, user.name) &&
				java.util.Objects.equals(s_bio, user.s_bio);
	}
	/* clone */
	@Override
	public User clone() {
		return new User(this);
	}
	/* Comparator<User> */
	@Override
	public int compareTo(User a) {
		int compare = ((User) a).get_n_posts();
		return compare-this.n_posts;
	}
}
