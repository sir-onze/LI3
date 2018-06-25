package engine;

import common.Pair;
import li3.TADCommunity;
import java.time.LocalDate;

import java.util.HashMap;
import java.util.List;
import java.util.TreeMap;

public class TCDCommunity implements TADCommunity {

	private HashMap<Long,User> users;
	private HashMap<Long,Post> posts;
	private HashMap<LocalDate,TreeMap<Long,Post>> answers;
	private HashMap<LocalDate,TreeMap<Long,Post>> questions;

	public void init() {
		this.users = new HashMap<Long,User>();
		this.posts = new HashMap<Long,Post>();
		this.answers = new HashMap <LocalDate,TreeMap<Long,Post>>();
		this.questions = new HashMap <LocalDate,TreeMap<Long,Post>>();
	}
	
    public void load(String dump_path) {
        String dump_path_users = dump_path + "/Users.xml";
        String dump_path_posts = dump_path + "/Posts.xml";
        Parser.parse_users(dump_path_users, this);
        Parser.parse_posts(dump_path_posts, this);
    }
    
    /* GETTERS */
    public HashMap<Long, User> get_users() { return this.users; }
    public HashMap<Long, Post> get_posts() { return this.posts; }
	public HashMap<LocalDate, TreeMap<Long, Post>> get_answers() { return this.answers; }
	public HashMap<LocalDate, TreeMap<Long, Post>> get_questions() { return this.questions; }
	
	/* ADDERS */
	public void add_user(User u) { this.users.put(u.get_id(),u); }
	public void add_post(Post p) { this.posts.put(p.get_id(), p); }
	public void add_question(Post p) {
		if(this.questions.containsKey(p.get_creation_date()))
			this.questions.get(p.get_creation_date()).put(p.get_id(), p);
		else {
			TreeMap<Long,Post> aux = new TreeMap<Long,Post>();
			aux.put(p.get_id(), p);
			this.questions.put(p.get_creation_date(),aux);
		}
	}
	public void add_answer(Post p) {
		if(this.answers.containsKey(p.get_creation_date()))
			this.answers.get(p.get_creation_date()).put(p.get_id(), p);
		else {
			TreeMap<Long,Post> aux = new TreeMap<Long,Post>();
			aux.put(p.get_id(), p);
			this.answers.put(p.get_creation_date(),aux);
		}
	}
	/************************************************************************
	 *                QUERIES -> QUERYENGINE                                *
	 ***********************************************************************/
	/* QUERY 1 */
    public Pair<String,String> infoFromPost(long id) {return QueryEngine.query_1(id,this);}
    /* Query 2 */
    public List<Long> topMostActive(int N) {return QueryEngine.query_2(N,this);}
    /* Query 3 */	
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {return QueryEngine.query_3(begin,end,this);}
    /* Query 4 */
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {return QueryEngine.query_4(tag,begin,end,this);}
    /* Query 5 */
    public Pair<String, List<Long>> getUserInfo(long id) {return QueryEngine.query_5(id,this);}
    /* Query 6*/
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {return QueryEngine.query_6(N,begin,end,this);}
    /* Query 7 */
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {return QueryEngine.query_7(N,begin,end,this);}
    /* Query 8 */
    public List<Long> containsWord(int N, String word) {return QueryEngine.query_8(N,word,this);}
    /* Query 9 */
    public List<Long> bothParticipated(int N, long id1, long id2) {return QueryEngine.query_9(N,id1,id2,this);}
    /* Query 10 */
    public long betterAnswer(long id) {return QueryEngine.query_10(id,this);}
    /* Query 11 */
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {return QueryEngine.query_11(N,begin,end,this);}
    /* Clear */
    public void clear(){
    	this.users.clear();
    	this.posts.clear();
    	this.questions.clear();
    	this.answers.clear();
    }
}
