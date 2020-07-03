DROP TABLE IF EXISTS users CASCADE;
DROP TABLE IF EXISTS cards CASCADE;
DROP TABLE IF EXISTS items CASCADE;
-- PREVIOUS TABLES ON TEACHERS PROJECT


-- Drop old content
DROP TABLE IF EXISTS item_history;
DROP TABLE IF EXISTS ban_user;
DROP TABLE IF EXISTS delete_comment;
DROP TABLE IF EXISTS stop_sale;
DROP TABLE IF EXISTS interest;
DROP TABLE IF EXISTS "action";
DROP TABLE IF EXISTS review;
DROP TABLE IF EXISTS "comment";
DROP TABLE IF EXISTS bid;
DROP TABLE IF EXISTS image_user;
DROP TABLE IF EXISTS image_item;
DROP TABLE IF EXISTS image;
DROP TABLE IF EXISTS notification_item;
DROP TABLE IF EXISTS notification_user;
DROP TABLE IF EXISTS notification;
DROP TABLE IF EXISTS auction_item;
DROP TABLE IF EXISTS purchase_item;
DROP TABLE IF EXISTS item;
DROP TABLE IF EXISTS moderator;
DROP TABLE IF EXISTS "user";

DROP TYPE IF EXISTS category;

DROP TRIGGER IF EXISTS comment_deleted_notification ON delete_comment;
DROP TRIGGER IF EXISTS sale_stopped_notification ON stop_sale;
DROP TRIGGER IF EXISTS delete_user_info ON "user";
DROP TRIGGER IF EXISTS notifications_from_bid ON bid;
DROP TRIGGER IF EXISTS check_email_valid_user ON "user";
DROP TRIGGER IF EXISTS check_email_valid_moderator ON moderator;
DROP TRIGGER IF EXISTS update_current_bid ON bid;
DROP TRIGGER IF EXISTS update_item_stopped ON stop_sale;
DROP TRIGGER IF EXISTS update_user_banned ON ban_user;
DROP TRIGGER IF EXISTS update_comment_deleted ON delete_comment;
DROP TRIGGER IF EXISTS delete_item ON item;
DROP TRIGGER IF EXISTS delete_comment ON comment;
DROP TRIGGER IF EXISTS notifications_from_comment ON comment;
DROP TRIGGER IF EXISTS notifications_from_review ON review;

DROP FUNCTION IF EXISTS comment_deleted_notification();
DROP FUNCTION IF EXISTS sale_stopped_notification();
DROP FUNCTION IF EXISTS delete_user_info();
DROP FUNCTION IF EXISTS notifications_from_bid();
DROP FUNCTION IF EXISTS check_email_valid();
DROP FUNCTION IF EXISTS update_current_bid();
DROP FUNCTION IF EXISTS set_item_stopped();
DROP FUNCTION IF EXISTS set_user_banned();
DROP FUNCTION IF EXISTS set_comment_deleted();
DROP FUNCTION IF EXISTS delete_item();
DROP FUNCTION IF EXISTS delete_comment();
DROP FUNCTION IF EXISTS notifications_from_comment();
DROP FUNCTION IF EXISTS notifications_from_review();

-- Types

CREATE TYPE category AS ENUM ('Painting', 'Sculpture', 'Photography', 'Drawing', 'Serigraphy', 'Ceramics');

-- Tables 

CREATE TABLE "user" (
    id         SERIAL PRIMARY KEY,
    "name" TEXT NOT NULL,
    email       TEXT    NOT NULL
                        UNIQUE,
    reputation  REAL,
    phone_number TEXT,
    biography   TEXT,
    "password"    TEXT    NOT NULL,
    banned BOOLEAN NOT NULL,
    is_admin BOOLEAN NOT NULL,
    cash REAL
);

CREATE TABLE interest (
    id SERIAL PRIMARY KEY,
    user_id   INTEGER REFERENCES "user" (id) NOT NULL,
    TYPE category NOT NULL
);

CREATE TABLE item (
    id          SERIAL PRIMARY KEY,
    title       TEXT    NOT NULL,
    seller_id   INTEGER REFERENCES "user" (id) 
                        NOT NULL,
    buyer_id   INTEGER REFERENCES "user" (id),
    TYPE category NOT NULL,
    description TEXT    NOT NULL,
    start_time   DATE    NOT NULL,
    stopped     BOOLEAN  NOT NULL    
);

CREATE TABLE auction_item (
    item_id            INTEGER PRIMARY KEY 
                          REFERENCES item (id) 
                          NOT NULL,
    starting_bid   REAL    NOT NULL,
    bid_difference REAL    NOT NULL,
    end_time       TIMESTAMP    NOT NULL,
    current_bid    REAL
);

CREATE TABLE purchase_item (
    item_id            INTEGER PRIMARY KEY 
                          REFERENCES item (id) 
                          NOT NULL,
    price REAL    NOT NULL
);

CREATE TABLE item_history (
    buyer_id   INTEGER REFERENCES "user" (id)
                        NOT NULL,
    seller_id   INTEGER REFERENCES "user" (id) 
                        NOT NULL,
    title TEXT NOT NULL,
    price REAL NOT NULL,
    reviewed BOOLEAN NOT NULL,
    PRIMARY KEY (
        buyer_id,
        seller_id,
        title
    )
);

CREATE TABLE "comment" (
    id      SERIAL PRIMARY KEY,
    user_id INTEGER REFERENCES "user" (id) 
                    NOT NULL,
    item_id INTEGER REFERENCES item (id) 
                    NOT NULL,
    "content" TEXT    NOT NULL,
    "date"    DATE    NOT NULL,
     deleted  BOOLEAN NOT NULL
);

CREATE TABLE review (
    buyer_id     INTEGER REFERENCES "user" (id) NOT NULL,
    seller_id   INTEGER REFERENCES "user" (id) NOT NULL,
    title TEXT NOT NULL,
    description TEXT,
    rating      INTEGER NOT NULL
                        CHECK (rating >= 0 AND 
                               rating <= 5),
    PRIMARY KEY (
        buyer_id,
        seller_id,
        title
    )
);

CREATE TABLE "action" (
    id         SERIAL PRIMARY KEY,
    moderator_id     INTEGER REFERENCES "user" (id) NOT NULL,
    reason     TEXT NOT NULL,
    "date"    DATE NOT NULL
);

CREATE TABLE ban_user (
    action_id            INTEGER PRIMARY KEY 
                          REFERENCES "action" (id) 
                          NOT NULL,
    user_id    INTEGER REFERENCES "user" (id) NOT NULL
);

CREATE TABLE delete_comment (
    action_id            INTEGER PRIMARY KEY 
                          REFERENCES "action" (id) 
                          NOT NULL,
    comment_id INTEGER REFERENCES "comment" (id) NOT NULL
);

CREATE TABLE stop_sale (
    action_id            INTEGER PRIMARY KEY 
                          REFERENCES "action" (id) 
                          NOT NULL,
    item_id    INTEGER REFERENCES item (id) NOT NULL
);

CREATE TABLE notification (
    id          SERIAL PRIMARY KEY,
    user_id     INTEGER REFERENCES "user" (id) 
                        NOT NULL,
    description TEXT    NOT NULL,
    "date"        TIMESTAMP    NOT NULL
);

CREATE TABLE notification_item (
  notification_id	INTEGER	REFERENCES notification (ID)
  					NOT NULL,
  item_id			INTEGER REFERENCES item (ID) NOT NULL
);

CREATE TABLE notification_user (
  notification_id	INTEGER REFERENCES notification (ID)
  					NOT NULL,
  user_id			INTEGER REFERENCES "user" (ID) NOT NULL
);

CREATE TABLE bid (
    id          SERIAL PRIMARY KEY,
    bidder_id    INTEGER REFERENCES "user" (id) 
                       NOT NULL,
    item_id    INTEGER REFERENCES item (id) 
                       NOT NULL,
    bid_amount DOUBLE PRECISION  NOT NULL,
    "date"       DATE    NOT NULL
);

CREATE TABLE image (
    id      SERIAL PRIMARY KEY,
    url     TEXT NOT NULL 
);

CREATE TABLE image_user (
    image_id    INTEGER REFERENCES image (id) NOT NULL,
    user_id INTEGER REFERENCES "user" (id) NOT NULL
);

CREATE TABLE image_item (
    image_id    INTEGER REFERENCES image (id) NOT NULL,
    item_id INTEGER REFERENCES item (id) NOT NULL
);
-- Indexes

CREATE INDEX review_reviewed ON review USING hash(seller_id);

CREATE INDEX item_amount_index_bid ON bid USING btree (item_id, bid_amount);

CREATE INDEX item_index_comment ON "comment" USING hash (item_id);

CREATE INDEX idx_notification ON notification USING hash (user_id);

CREATE INDEX idx_image_user ON image_user USING hash (user_id);

CREATE INDEX idx_image_item ON image_item USING hash (item_id);

CREATE INDEX full_text_search_idx ON item USING GIST (to_tsvector('english', title)); 

-- Triggers and Functions

CREATE FUNCTION comment_deleted_notification() returns trigger as
$BODY$
DECLARE
	temp_user_id INTEGER;
    temp_item_id INTEGER;
BEGIN
    SELECT INTO temp_user_id user_id FROM "comment"
        WHERE "comment".ID = new.comment_id;
    SELECT INTO temp_item_id item_id FROM "comment"
        WHERE "comment".ID = new.comment_id;
    INSERT INTO notification (user_id, description, "date") VALUES (temp_user_id, 'Your comment has been deleted on: ' || temp_item_id, now());
    INSERT INTO notification_item (notification_id, item_id) VALUES (currval('notification_id_seq'), temp_item_id);
RETURN NEW;
END
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER comment_deleted_notification
	AFTER INSERT ON delete_comment
    FOR EACH ROW
    EXECUTE PROCEDURE comment_deleted_notification();  
    
CREATE FUNCTION sale_stopped_notification() returns trigger as
$BODY$
DECLARE
    temp_user_id INTEGER;
BEGIN
    FOR temp_user_id IN
        SELECT DISTINCT bidder_id FROM bid WHERE item_id = NEW.item_id
    LOOP
        INSERT INTO notification (user_id, description, "date") VALUES (temp_user_id, 'The following auction item sale got stopped: ' || NEW.item_id, now());
        INSERT INTO notification_item (notification_id, item_id) VALUES (currval('notification_id_seq'), NEW.item_id);
    END LOOP;
    SELECT INTO temp_user_id seller_id FROM item
        WHERE item.ID = new.item_id;
    INSERT INTO notification (user_id, description, "date") VALUES (temp_user_id, 'Your auction item has been stopped: ' ||  NEW.item_id, now());
    INSERT INTO notification_item (notification_id, item_id) VALUES (currval('notification_id_seq'),  NEW.item_id);
RETURN NEW;    
END
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER sale_stopped_notification
	AFTER INSERT ON stop_sale
    FOR EACH ROW
    EXECUTE PROCEDURE sale_stopped_notification();  

CREATE FUNCTION delete_user_info() RETURNS TRIGGER AS
$BODY$
BEGIN
    DELETE FROM interests WHERE (interests.user_id = OLD.id);
    UPDATE item SET buyer_id = '0' WHERE buyer_id = OLD.id;
    UPDATE item SET seller_id = '0' WHERE seller_id = OLD.id;
    UPDATE "comment" SET user_id = '0' WHERE user_id = OLD.id;
    DELETE FROM review WHERE (review.seller_id = OLD.id);
    UPDATE review SET buyer_id = '0' WHERE buyer_id = OLD.id;
    DELETE FROM notification WHERE (notification.user_id = OLD.id);
    DELETE FROM ban_user WHERE (ban_user.user_id = OLD.id);
    DELETE FROM bid WHERE (bid.bidder_id = OLD.id);
    DELETE FROM image_user WHERE (image_user.user_id = OLD.id);
RETURN OLD;    
END
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER delete_user_info
    BEFORE DELETE ON "user"
    FOR EACH ROW
    EXECUTE PROCEDURE delete_user_info();

CREATE FUNCTION notifications_from_bid() RETURNS TRIGGER AS
$BODY$
DECLARE
	temp_user INTEGER;
    temp_owner INTEGER;
BEGIN
	FOR temp_user IN
        SELECT DISTINCT bidder_id FROM bid WHERE item_id = NEW.item_id AND bidder_id != NEW.bidder_id
    LOOP
        INSERT INTO notification (user_id, description, "date") VALUES (temp_user, 'A new bid has been made on an item you bid on', now());
        INSERT INTO notification_item (notification_id, item_id) VALUES (currval('notification_id_seq'),  NEW.item_id);
    END LOOP;
    FOR temp_owner IN
        SELECT DISTINCT seller_id FROM item WHERE id = NEW.item_id
    LOOP
        INSERT INTO notification (user_id, description, "date") VALUES (temp_owner, 'A new bid has been made on your item', now());
        INSERT INTO notification_item (notification_id, item_id) VALUES (currval('notification_id_seq'),  NEW.item_id);
    END LOOP;
RETURN NEW;
END
$BODY$
LANGUAGE plpgsql;
 
CREATE TRIGGER notifications_from_bid
    AFTER INSERT ON bid
    FOR EACH ROW
    EXECUTE PROCEDURE notifications_from_bid(); 
    
CREATE FUNCTION check_email_valid() RETURNS TRIGGER AS  
$BODY$  
BEGIN  	
    IF EXISTS (SELECT email FROM "user" WHERE email = NEW.email) THEN
        RAISE EXCEPTION 'User with same email already exists';      
    END IF;        
RETURN NEW;
END  
$BODY$  
LANGUAGE plpgsql;     

CREATE TRIGGER check_email_valid_user      
    BEFORE INSERT ON "user"      
    FOR EACH ROW      
    EXECUTE PROCEDURE check_email_valid();
    
CREATE FUNCTION update_current_bid() RETURNS TRIGGER AS  
$BODY$  
BEGIN  
UPDATE auction_item       
    SET current_bid = NEW.bid_amount       
    WHERE item_id = NEW.item_id;      
RETURN NEW;  
END  
$BODY$  
LANGUAGE plpgsql;  

CREATE TRIGGER update_current_bid      
    AFTER INSERT ON bid      
    FOR EACH ROW     
    EXECUTE PROCEDURE update_current_bid();


CREATE FUNCTION set_item_stopped() RETURNS TRIGGER AS  
$BODY$  
BEGIN  
UPDATE item       
    SET stopped = true       
    WHERE id = new.item_id;      
RETURN NEW;  
END  
$BODY$  
LANGUAGE plpgsql;  

CREATE TRIGGER update_item_stopped      
    AFTER INSERT ON stop_sale      
    FOR EACH ROW     
    EXECUTE PROCEDURE set_item_stopped();


CREATE FUNCTION set_user_banned() RETURNS TRIGGER AS  
$BODY$  
BEGIN  
UPDATE "user"       
    SET banned = true       
    WHERE id = new.user_id;      
RETURN NEW;  
END  
$BODY$  
LANGUAGE plpgsql;  

CREATE TRIGGER update_user_banned
    AFTER INSERT ON ban_user      
    FOR EACH ROW     
    EXECUTE PROCEDURE set_user_banned();


CREATE FUNCTION set_comment_deleted() RETURNS TRIGGER AS  
$BODY$  
BEGIN  
UPDATE "comment"       
    SET deleted = true       
    WHERE id = new.comment_id;      
RETURN NEW;  
END  
$BODY$  
LANGUAGE plpgsql;  

CREATE TRIGGER update_comment_deleted
    AFTER INSERT ON delete_comment      
    FOR EACH ROW     
    EXECUTE PROCEDURE set_comment_deleted();


CREATE FUNCTION delete_item() returns trigger AS 
$BODY$
BEGIN
    DELETE FROM auction_item
        WHERE old.id = auction_item.item_id;
    DELETE FROM purchase_item
        WHERE old.id = purchase_item.item_id;
    DELETE FROM "comment"
        WHERE old.id = "comment".item_id;
    DELETE FROM notification_item
        WHERE old.id = notification_item.item_id;
    DELETE FROM bid
        WHERE old.id = bid.item_id;
    DELETE FROM image_item
        WHERE old.id = image_item.item_id;
RETURN OLD;
END
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER delete_item
	BEFORE DELETE ON item
    FOR EACH ROW
    EXECUTE PROCEDURE delete_item(); 
    

CREATE FUNCTION delete_comment() returns trigger AS
$BODY$
BEGIN
    DELETE FROM delete_comment
        WHERE old.id = delete_comment.comment_id;
RETURN OLD;
END
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER delete_comment
    BEFORE DELETE ON "comment"
    FOR EACH ROW
    EXECUTE PROCEDURE delete_comment(); 


CREATE FUNCTION notifications_from_comment() returns trigger AS
$BODY$
DECLARE
	temp_user INTEGER;
BEGIN
	FOR temp_user IN
        SELECT DISTINCT seller_id FROM item WHERE id = NEW.item_id
    LOOP
        INSERT INTO notification (user_id, description, "date") VALUES (temp_user, 'A new comment has been made on one of your items', now());
        INSERT INTO notification_item (notification_id, item_id) VALUES (currval('notification_id_seq'),  NEW.item_id);
    END LOOP;
RETURN NEW;
END
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER notifications_from_comment
    AFTER INSERT ON "comment"
    FOR EACH ROW
    EXECUTE PROCEDURE notifications_from_comment();


CREATE FUNCTION notifications_from_review() returns trigger AS
$BODY$
BEGIN
    INSERT INTO notification (user_id, description, "date") VALUES (NEW.seller_id, 'A user made you a review', now());
    INSERT INTO notification_user (notification_id, user_id) VALUES (currval('notification_id_seq'),  NEW.buyer_id);
RETURN NEW;
END
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER notifications_from_review
    AFTER INSERT ON "review"
    FOR EACH ROW
    EXECUTE PROCEDURE notifications_from_review();


INSERT INTO "user" VALUES ( 0, 'placeholder', 'placeholder', 0, 'placeholder', 'placeholder', 'placeholder', 'false', 'false', 0);
INSERT INTO "user" VALUES ( 1, 'Tiago Verdade', 'tiago@hotmail.com', 1, '91239123', 'ola a todos', 'adsadadda', 'false', 'false', 0);
INSERT INTO "user" VALUES ( 2, 'Art Studio', 'artstudio@hotmail.com', 5, '2314124', 'Comprem as nossas cenas', '$2y$10$HfzIhGCCaxqyaIdGgjARSuOKAcm1Uy82YfLuNaajn6JrjLWy9Sj/W', 'false', 'false', 0);
INSERT INTO "user" VALUES ( 3, 'Diogo Sousa', 'diogo@hotmail.com', 0, '912381351', '', '$2y$10$HfzIhGCCaxqyaIdGgjARSuOKAcm1Uy82YfLuNaajn6JrjLWy9Sj/W', 'false', 'false', 0);
INSERT INTO "user" VALUES ( 4, 'User', 'user@hotmail.com', 0, '91239123', '', 'qwertyuiop', 'false', 'false', 0);
INSERT INTO "user" VALUES ( 5, 'Museu Coimbra', 'coimbra_museum@hotmail.com', 0, '239123592', 'Bem vindos a nossa colecao', 'birthday123', 'false', 'false', 0);
INSERT INTO "user" VALUES ( 6, 'testing website', 'test123@hotmail.com', 0, '', '', 'washingmachine', 'false', 'false', 0);

INSERT INTO "user" VALUES (7,'Rafael','rafael@example.com',0.0,'914249435','','$2y$10$HfzIhGCCaxqyaIdGgjARSuOKAcm1Uy82YfLuNaajn6JrjLWy9Sj/W','false', 'false', 0);
-- mods
INSERT INTO "user" VALUES (8, 'Admin', 'admin@artbay.pt', NULL, NULL, NULL, '$2y$10$HfzIhGCCaxqyaIdGgjARSuOKAcm1Uy82YfLuNaajn6JrjLWy9Sj/W', 'false', 'true', 0);
INSERT INTO "user" VALUES (9, 'Supervisor', 'supervisor@artbay.pt', NULL, NULL, NULL, '19051970abc', 'false', 'true', 0);
INSERT INTO "user" VALUES (10, 'CEO', 'ceo@artbay.pt', NULL, NULL, NULL, 'cupcake123', 'false', 'true', 0);

SELECT setval('user_id_seq', max(id)) FROM "user";

INSERT INTO interest VALUES ( 1, 1, 'Painting');
INSERT INTO interest VALUES ( 2, 1, 'Sculpture');
INSERT INTO interest VALUES ( 3, 2, 'Photography');
INSERT INTO interest VALUES ( 4, 2, 'Painting');
INSERT INTO interest VALUES ( 5, 3, 'Ceramics');
INSERT INTO interest VALUES ( 6, 5, 'Painting');
INSERT INTO interest VALUES ( 7, 5, 'Sculpture');
INSERT INTO interest VALUES ( 8, 5, 'Photography');
INSERT INTO interest VALUES ( 9, 7, 'Serigraphy');
INSERT INTO interest VALUES ( 10, 7, 'Ceramics');

SELECT setval('interest_id_seq', max(id)) FROM "interest";

INSERT INTO item VALUES ( 1, 'Mona Lisa', 2, 1, 'Painting', 'Muito bonito', timestamp '2020-04-28 01:00:00', 'false');
INSERT INTO item VALUES ( 2, 'Fake Mona Lisa', 2, NULL, 'Painting', 'Nao tao bonito', timestamp '2020-04-29 01:00:00', 'false');
INSERT INTO item VALUES ( 3, 'Venus de Milo', 7, NULL, 'Sculpture', 'Incredible artwork', timestamp '2020-05-02 14:30:00', 'false');
INSERT INTO item VALUES ( 4, 'Saturn Devouring His Son', 5, NULL, 'Painting', 'Painting by Francisco Goya (1746-1828)', timestamp '2020-06-02 15:50:33', 'false');

SELECT setval('item_id_seq', max(id)) FROM "item";

INSERT INTO auction_item VALUES ( 2, 2000, 10, timestamp '2020-06-02 16:00:00');
INSERT INTO auction_item VALUES ( 3, 150000, 1000, timestamp '2020-06-02 14:30:00');
INSERT INTO purchase_item VALUES ( 1, 300000);
INSERT INTO purchase_item VALUES (4, 600000);

INSERT INTO item_history VALUES (2, 5, 'Saturn Devouring His Son', 600000, 'false');
INSERT INTO item_history VALUES (2, 3, 'Mona Lisa', 300000, 'true');
INSERT INTO item_history VALUES (2, 7, 'Venus de Milo', 250000, 'false');

INSERT INTO "comment" VALUES ( 1, 1, 1, 'Good item!', timestamp '2020-04-29 23:00:00', 'false');
INSERT INTO "comment" VALUES ( 2, 2, 1, 'Thanks', timestamp '2020-04-29 23:01:00', 'false');
INSERT INTO "comment" VALUES ( 3, 6, 3, 'SPAM SPAM SPAM SPAM', timestamp '2020-05-03 23:02:00', 'false');
INSERT INTO "comment" VALUES ( 4, 3, 3, 'Interesting piece. Sadly it is too expensive for me.', timestamp '2020-05-05 23:02:00', 'false');
INSERT INTO "comment" VALUES ( 5, 7, 3, 'Sorry to hear that, but thank you', timestamp '2020-05-06 11:02:45', 'false');

SELECT setval('comment_id_seq', max(id)) FROM "comment";

INSERT INTO review VALUES (1, 2, 'Mona Lisa', 'Not so good but ok.', 3);
INSERT INTO review VALUES (7, 2, 'Mona Lisa', 'Item arrived in perfect conditions.', 5);

INSERT INTO "action" VALUES ( 1, 8, 'Is spam', timestamp '2020-05-04 09:05:00');
INSERT INTO "action" VALUES ( 2, 9, 'Violated principles', timestamp '2020-05-04 09:10:00');

SELECT setval('action_id_seq', max(id)) FROM "action";

INSERT INTO delete_comment VALUES (1, 3);
INSERT INTO ban_user VALUES (2, 6);

INSERT into notification VALUES ( 101, 7, 'You have been outbid on an item: Mona Lisa', timestamp '2020-04-29 23:30:00');
INSERT into notification VALUES ( 102, 3, 'You have been outbid on an item: Mona Lisa', timestamp '2020-04-29 23:35:00');
INSERT into notification VALUES ( 103, 6, 'Your comment on the following item has been deleted: Venus de Milo', timestamp '2020-05-04 09:05:00');
INSERT into notification VALUES ( 104, 7, 'You have purchased an item: Mona Lisa', timestamp '2020-05-15 01:00:00');
INSERT into notification VALUES ( 105, 7, 'You have a new review', timestamp '2020-05-15 01:00:00');
INSERT into notification VALUES ( 106, 7, 'You have a new review', timestamp '2020-05-15 01:00:00');

SELECT setval('notification_id_seq', max(id)) FROM "notification";

INSERT into notification_item VALUES (101, 1);
INSERT into notification_item VALUES (104, 1);

INSERT into notification_user VALUES (105, 1);
INSERT into notification_user VALUES (106, 3);

INSERT INTO bid VALUES ( DEFAULT, 1, 2, 2005, timestamp '2020-04-29 23:00:00');
INSERT INTO bid VALUES ( DEFAULT, 3, 2, 2015, timestamp '2020-04-29 23:30:00');
INSERT INTO bid VALUES ( DEFAULT, 1, 2, 2020, timestamp '2020-04-29 23:35:00');

INSERT INTO image VALUES (1, 'user1image.png');
INSERT INTO image VALUES (2, 'user2image.png');
INSERT INTO image VALUES (3, 'user3image.png');
INSERT INTO image VALUES (4, 'item1image1.png');
INSERT INTO image VALUES (5, 'item1image2.png');
INSERT INTO image VALUES (6, 'item2image1.png');
INSERT INTO image VALUES (7, 'item2image2.png');
INSERT INTO image VALUES (8, 'item2image3.png');
INSERT INTO image VALUES (9, 'user5image.png');
INSERT INTO image VALUES (10, 'rafael.png');
INSERT INTO image VALUES (11, 'item4_image1.jpg');

SELECT setval('image_id_seq', max(id)) FROM "image";

insert into image_user VALUES (1, 1);
insert into image_user VALUES (2, 2);
insert into image_user VALUES (3, 3);
insert into image_user VALUES (9, 5);
insert into image_user VALUES (10, 7);

insert into image_item VALUES (4, 1);
insert into image_item VALUES (5, 1);
insert into image_item VALUES (6, 2);
insert into image_item VALUES (7, 2);
insert into image_item VALUES (8, 2);
INSERT INTO image_item VALUES (11, 4);