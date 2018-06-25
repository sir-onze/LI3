package engine;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.TreeMap;
import java.util.stream.Collectors;

import common.Pair;

public class QueryEngine {
	
	/* Query 1 */
	public static Pair<String,String>query_1(long id,TCDCommunity tcd) {
		String title = null, username=null;
    	long owner_id=0, parent_id=0;
    	Post p = tcd.get_posts().get(id);
    	if(p.get_post_type() == 1) {
    		title = p.get_title();
    		owner_id = p.get_owner_id();
    		username = tcd.get_users().get(owner_id).get_name();
    	}
    	if(p.get_post_type() == 2) {
    		parent_id = p.get_parent_id();
    		p = tcd.get_posts().get(parent_id);
    		title = p.get_title();
    		owner_id = p.get_owner_id();
    		username = tcd.get_users().get(owner_id).get_name();
    	}
        return new Pair<String,String>(title,username);
	}
	
	/* Query 2 */
	public static List<Long> query_2(int N,TCDCommunity tcd) {
		ArrayList<User> u = new ArrayList<User>(tcd.get_users().values());
		Collections.sort(u);
		return u.stream().map(User::get_id).limit(N).collect(Collectors.toList());
	}
	
	/* Query 3 */
	public static Pair<Long,Long> query_3(LocalDate begin, LocalDate end,TCDCommunity tcd) {
		long questions= count_post(begin, end, 1,tcd);
		long answers = count_post(begin, end, 2,tcd);
		return new Pair<Long,Long>(questions,answers);
	}
	 
	/* Query 4 */
	public static List<Long> query_4(String tag, LocalDate begin, LocalDate end, TCDCommunity tcd) {
		ArrayList<Post> aux = new ArrayList<Post>();
		for(LocalDate key : tcd.get_questions().keySet()) {
			if(key.isAfter(begin) && key.isBefore(end)) {
				TreeMap<Long,Post> tr = tcd.get_questions().get(key);
				for(Long p_key: tr.keySet()) {
					if(tr.get(p_key).get_tags().contains(tag))
						aux.add(tr.get(p_key));
				}
			}
		}
		Collections.sort(aux, new Comparator<Post>() {
			public int compare(Post a, Post b) {
				if (a.get_creation_date() == null || b.get_creation_date() == null)
					return 0;
				return b.get_creation_date().compareTo(a.get_creation_date());
			}
		});
		return aux.stream().map(Post::get_id).collect(Collectors.toList());
	}
	 
	/* Query 5 */
	public static Pair<String, List<Long>> query_5(long id,TCDCommunity tcd) {
		User u = tcd.get_users().get(id);
		String shortBio = u.get_s_bio();
		ArrayList<Post> l = new ArrayList<Post>(u.get_posts());
		Collections.sort(l, new Comparator<Post>() {
			public int compare(Post a, Post b) {
				if (a.get_creation_date() == null || b.get_creation_date() == null)
					return 0;
				return b.get_creation_date().compareTo(a.get_creation_date());
			}
		});
		List<Long> aux = l.stream().map(Post::get_id).limit(10).collect(Collectors.toList());
		return new Pair<>(shortBio,aux);
	}
	
	/* Query 6*/
	public static List<Long> query_6(int N, LocalDate begin, LocalDate end, TCDCommunity tcd) {
		ArrayList<Post> aux = new ArrayList<Post>();
		for(LocalDate key : tcd.get_questions().keySet()) {
			TreeMap<Long,Post> tr = tcd.get_questions().get(key);
			for(Long key_p : tr.keySet()) { 
					aux.add(tr.get(key_p));
			}
		}
		Collections.sort(aux, new Comparator<Post>() {
			public int compare(Post a, Post b) {
				return Long.compare(a.get_score(),b.get_score());
			}
		});
		
		return aux.stream().map(Post::get_id).limit(N).collect(Collectors.toList());	
	}
	
	/* Query 7 */
	public static List<Long> query_7(int N, LocalDate begin, LocalDate end, TCDCommunity tcd) {
		ArrayList<Post> aux = new ArrayList<Post>();
		for(LocalDate key : tcd.get_questions().keySet()) {
			TreeMap<Long,Post> tr = tcd.get_questions().get(key);
			for(Long key_p : tr.keySet()) { 
					aux.add(tr.get(key_p));
			}
		}
		Collections.sort(aux, new Comparator<Post>() {
			public int compare(Post a, Post b) {
				return Integer.compare(b.get_answers_count(),a.get_answers_count());
			}
		});
		
		return aux.stream().map(Post::get_id).limit(N).collect(Collectors.toList());	
	}
	
	/* Query 8 */
	public static List<Long> query_8 (int N, String word, TCDCommunity tcd) {
		ArrayList<Post> aux = new ArrayList<Post>();
		for(LocalDate key : tcd.get_questions().keySet()) {
			TreeMap<Long,Post> tr = tcd.get_questions().get(key);
			for(Long key_p : tr.keySet()) {
				if(tr.get(key_p).get_title().contains(word)) {
					aux.add(tr.get(key_p));
				}
			}
		}
		Collections.sort(aux, new Comparator<Post>() {
			public int compare(Post a, Post b) {
				if (a.get_creation_date() == null || b.get_creation_date() == null)
					return 0;
				return b.get_creation_date().compareTo(a.get_creation_date());
			}
		});
		return aux.stream().map(Post::get_id).limit(N).collect(Collectors.toList());
	}
	
	/* Query 9*/
	public static List<Long> query_9(int N, long id1, long id2,TCDCommunity tcd) {
		return null;
	}
	
	/* Query 10 */
	public static long query_10(long id, TCDCommunity tcd) {
		double score_answer=0;
		double best_answer=0;
		long best_answer_id=0;
		Post p;User u;
		for(Long key : tcd.get_posts().keySet()) {
			if(tcd.get_posts().get(key).get_parent_id()==id) {
				u=tcd.get_users().get(tcd.get_posts().get(key).get_owner_id());
				p=tcd.get_posts().get(key);
				score_answer=0.45*p.get_score()+0.25*u.get_reputation()+0.2*p.get_score()+0.1*p.get_comment_count();
				if(score_answer>best_answer) {
					best_answer=score_answer;
					best_answer_id=tcd.get_posts().get(key).get_id();
				}
			}
		}
		return best_answer_id;
	}
	
	/* Query 11 */
	public static List<Long> query_11(int N, LocalDate begin, LocalDate end,TCDCommunity tcd) {
		return null;
	}
	
	/* Funçoes auxiliares */
	public static long count_post(LocalDate a,LocalDate b,int p,TCDCommunity tcd) {
		long r=0;
		if(p==1) {
			for(LocalDate key : tcd.get_questions().keySet()) {
				if(key.isAfter(a) && key.isBefore(b))
					r+=tcd.get_questions().get(key).size(); }
		}
		if(p==2) {
			for(LocalDate key : tcd.get_answers().keySet()) {
				if(key.isAfter(a) && key.isBefore(b))
					r+= tcd.get_answers().get(key).size(); }
		}
		return r;
	}
	
}
