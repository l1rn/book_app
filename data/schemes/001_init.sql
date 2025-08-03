
create table Author (
    id integer primary key,
    name text NOT NULL,
    surname text NOT NULL
);

create table Publisher (
   id integer primary key,
   bookCount integer DEFAULT 0,
   companyName text NOT NULL
);

create table Book (
      isbn13 integer primary key,
      isbn10 integer,
      bookName text NOT NULL,
      publicationDate text,
      pages integer,
      publisherId integer,
      foreign key (publisherId) references Publisher(id)
);

create table BookAuthor (
    isbn13 integer,
    authorId integer,
    primary key (isbn13, authorId),
    foreign key (isbn13) references Book(isbn13),
    foreign key (authorId) references Author(id)
);