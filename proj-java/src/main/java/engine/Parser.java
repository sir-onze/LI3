package engine;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;

public class Parser {
	/* Método que efetua o parse dos Users e posterior inserção nas estruturas de dados */
	public static void parse_users(String filename, TCDCommunity tcd) {
		int event, reputation=0;
		long id = 0;
		String name = null, s_bio = null, attr = null;
		User u;
		
		try {
			/* Construção dos métodos para travessia do documento usando o StreamReader*/
			XMLInputFactory factory = XMLInputFactory.newInstance();
			factory.setProperty(XMLInputFactory.IS_COALESCING,true);
			XMLStreamReader eventReader = factory.createXMLStreamReader(new FileInputStream(new File(filename)));
			/* Inicio da travessia */
			while(eventReader.hasNext()) {
				event = eventReader.next();
				if(event == XMLStreamConstants.START_ELEMENT) {
					if (eventReader.getLocalName().equals("row"))
					/*Guardar a variável ID para a estrututra*/
						attr = eventReader.getAttributeValue(null, "Id");               
					if (attr != null) {
						id = Long.parseLong(attr);}
					/*Guardar a variável Reputation para a estrututra*/
					attr = eventReader.getAttributeValue(null, "Reputation");
					if (attr != null){
						reputation = Integer.parseInt(attr);}
					/*Guardar a variável nome para a estrututra*/
					attr = eventReader.getAttributeValue(null, "DisplayName");
					if (attr != null){
						name = attr;}
					/*Guardar a variável Short Bio para a estrututra*/
					attr = eventReader.getAttributeValue(null, "AboutMe");
					if (attr != null){
						s_bio= attr.trim().replaceAll("\n", "");}
					if(id>0){
						u = new User(id, reputation, name, s_bio, 0);
						tcd.add_user(u);
					}
				}
			}
		}
		catch (FileNotFoundException e) {
			e.printStackTrace();}
		catch (XMLStreamException e) {
			e.printStackTrace();}
	}
	
	/* Método que efetua o parse dos Posts e posterior inserção nas estruturas de dados */
	public static void parse_posts(String filename, TCDCommunity tcd) {
		String attr_id=null, attr_owner_id=null, attr_parent_id=null, attr_score=null, attr_post_type=null, attr_comment_count=null;
		String attr_creation_date=null, attr_title=null, attr_tags=null;

		long id=0, owner_id=0, parent_id=0, score=0;
		int post_type=0, comment_count=0, answer_count=0;
		LocalDate creation_date=null;
		String title=null, tags=null;
		int event;
		String text=null;
		
		Post p;User u;
		
		try {
			/* Construção dos métodos para travessia do documento usando o StreamReader*/
			XMLInputFactory factory = XMLInputFactory.newInstance();
			factory.setProperty(XMLInputFactory.IS_COALESCING,true);
			XMLStreamReader eventReader = factory.createXMLStreamReader(new FileInputStream(new File(filename)));
			/* Inicio da travessia */
			while(eventReader.hasNext()) {
				event = eventReader.next();
				if(event == XMLStreamConstants.START_ELEMENT) {
					text = eventReader.getLocalName();
					if (text.equals("row")) {
						/* Guardar as variáveis para posterior inserção na estrututra */
						attr_owner_id = eventReader.getAttributeValue(null, "OwnerUserId");               
						attr_id = eventReader.getAttributeValue(null, "Id");  
						attr_post_type = eventReader.getAttributeValue(null, "PostTypeId");
						attr_creation_date = eventReader.getAttributeValue(null, "CreationDate");
						attr_title = eventReader.getAttributeValue(null, "Title");
						attr_tags = eventReader.getAttributeValue(null, "Tags");
						attr_score = eventReader.getAttributeValue(null, "Score");
						attr_comment_count = eventReader.getAttributeValue(null, "CommmentCount");
					}
					/* verificação se posts tem owner id e não é o default */
					if(attr_owner_id!=null){
						owner_id = Long.parseLong(attr_owner_id);
						id = Long.parseLong(attr_id);
						post_type = Integer.parseInt(attr_post_type);
						if( post_type==2 ){
		                    attr_parent_id = eventReader.getAttributeValue(null, "ParentId");
		                    parent_id = Long.parseLong(attr_parent_id);
		                }
						if( post_type==1 ){
			                    parent_id = 0;
			            }
					}
			        else{
			        	post_type = 0;
			            parent_id = 0;
			        }
					/* Creation date */
					if(attr_creation_date!=null) creation_date = to_date(attr_creation_date);
					/* Tittle */
					title = attr_title;
					/* Tags */
					tags = attr_tags;
					/* Score */
					if(attr_score!=null) score = Integer.parseInt(attr_score);
					/* Score */
					if(attr_comment_count!=null) comment_count = Integer.parseInt(attr_comment_count);
					/* Criação do objeto post*/
					p = new Post(id, owner_id, parent_id, score, post_type, answer_count, comment_count, creation_date, title, tags);
					/* Procura e incremento da variavel n_posts do owner_user_id */
					u = tcd.get_users().get(owner_id);
					if(u!=null) {
						u.set_n_posts(); //u pode ser null caso o autor do post seja o -1
						/* Atualizar o user_posts */
						u.add_post(p);
					}
					/* Inserçao na hash geral dos Posts*/
					tcd.add_post(p);
					/* Caso seja uma pergunta */
					if(post_type == 1)
						tcd.add_question(p);
					/* Caso seja uma resposta */
					if(post_type == 2)
						tcd.add_answer(p);
				}
			}
		}
		catch (FileNotFoundException e) {
			e.printStackTrace();}
		catch (XMLStreamException e) {
			e.printStackTrace();}
	}
	
	/* Metodo que permite a passagem da String que representa uma data de um post e cria uma LocalDate para ser usada como 
	 * atributo de um Post */
	public static LocalDate to_date(String string){
		LocalDate d=null;
		String year=null,month=null,day=null,date=null;
		/* Dividir a string em ano mes e dia com caracteres extra */
		String[] parts = string.split("-");
		year = parts[0];
		month = parts[1];
		day = parts[2];
		String parts_2[] = day.split("T");
		day = parts_2[0];
		/* Passagem de String para LocalDate */
		DateTimeFormatter formatter = DateTimeFormatter.ofPattern("d/MM/yyyy");
		date = new StringBuilder()
		    .append(day)
		    .append("/")
		    .append(month)
		    .append("/")
		    .append(year)
		    .toString();
		d = LocalDate.parse(date, formatter);
		return d;
	}
}