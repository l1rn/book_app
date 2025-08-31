
create table Author (
    id integer primary key autoincrement,
    name text NOT NULL,
    surname text NOT NULL
);

create table Publisher (
   id integer primary key autoincrement,
   book_count integer DEFAULT 0,
   company_name text NOT NULL
);

create table Book (
      isbn13 text primary key,
      isbn10 text,
      book_name text NOT NULL,
      publication_date text,
      pages integer,
      publisher_id integer,
      foreign key (publisher_id) references Publisher(id)
);

create table BookAuthor (
    isbn13 integer,
    author_id integer,
    primary key (isbn13, author_id),
    foreign key (isbn13) references Book(isbn13),
    foreign key (author_id) references Author(id)
);