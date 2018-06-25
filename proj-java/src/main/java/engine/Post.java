package engine;

import java.time.LocalDate;
import java.util.Objects;

public class Post{
	
    private long id, owner_id, parent_id,score;
    private int post_type,answers_count,comment_count;;
    private LocalDate creation_date;
    private String title;
    private String tags;
    
    /* Params Constructor */
    public Post(long id, long owner_id, long parent_id, long score, int post_type, int answers_count, int comment_count, LocalDate creation_date, String title, String tags) {
        this.id = id;
        this.owner_id = owner_id;
        this.parent_id = parent_id;
        this.score = score;
        this.post_type = post_type;
        this.answers_count = answers_count;
        this.comment_count = comment_count;
        this.creation_date = creation_date;
        this.title = title;
        this.tags = tags;
    }
    /* Copy Constructor */
    public Post(Post p) {
    	this.id = p.get_id();
        this.owner_id = p.get_owner_id();
        this.parent_id = p.get_parent_id();
        this.score = p.get_score();
        this.post_type = p.get_post_type();
        this.answers_count = p.get_answers_count();
        this.comment_count = p.get_comment_count();
        this.creation_date = p.get_creation_date();
        this.title = p.get_title();
        this.tags = p.get_tags();
    }
    
    /* Getters */
    public long get_id() { return id; }
    public long get_owner_id() { return owner_id; }
    public long get_parent_id() { return parent_id; }
    public long get_score() { return score; }
    public int get_post_type() { return post_type; }
    public int get_answers_count() { return answers_count; }
    public int get_comment_count() { return comment_count; }
    public LocalDate get_creation_date() { return creation_date; }
    public String get_title() { return title; }
    public String get_tags() { return tags; }
    /* Setters */
    public void set_id(long id) { this.id = id; }
    public void set_owner_id(long owner_id) { this.owner_id = owner_id; }
    public void set_parent_id(long parent_id) { this.parent_id = parent_id; }
    public void set_score(long score) { this.score = score; }
    public void set_post_type(int post_type) { this.post_type = post_type; }
    public void set_answers_count(int answers_count) { this.answers_count = answers_count; }
    public void set_comment_count(int comment_count) { this.comment_count = comment_count; }
    public void set_creation_date(LocalDate creation_date) { this.creation_date = creation_date; }
    public void set_title(String title) { this.title = title; }
    public void set_tags(String tags) { this.tags = tags; }
    
    /* Equals*/
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Post post = (Post) o;
        return id == post.id &&
                owner_id == post.owner_id &&
                parent_id == post.parent_id &&
                score == post.score &&
                post_type == post.post_type &&
                answers_count == post.answers_count &&
                comment_count == post.comment_count &&
                Objects.equals(creation_date, post.creation_date) &&
                Objects.equals(title, post.title) &&
                Objects.equals(tags, post.tags);
    }
    /* toString */
    @Override
	public String toString() {
		return "Post [id=" + id + ", owner_id=" + owner_id + ", parent_id=" + parent_id + ", score=" + score
				+ ", post_type=" + post_type + ", answers_count=" + answers_count + ", comment_count=" + comment_count
				+ ", creation_date=" + creation_date + ", title=" + title + ", tags=" + tags + "]";
	}
    /* Clone */
    @Override
    public Post clone(){
        return new Post(this);
    }
}