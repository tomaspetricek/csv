# CSV
It is a C++ library that allows reading and writing to CSV files.
It was designed with efficiency and simplicity in mind.
The library gives the programmer freedom, for example, in choosing a data structure for storing input/output data.
It has also been well tested.

## Reading
Reading is enabled using the `csv::reader` class.
It takes the number of columns of the CSV file and a parser as its class template parameters.
The default parser is `csv::parser`, which allows conversion of `std::string_view` to numbers, enums, and `std::string`.
A custom parser can also be provided.

The `read_header` method allows reading header into an instance of `std::array`.
Returns a boolean indicating whether it read the header.
Returns `false` if the file is empty.

The `read_row` method is used to read a row of the CSV file directly into the variables provided using the template parameter pack.
It returns `true` if the line has been read, `false` otherwise, so it can be used in a `while` loop to read the entire file.
Throws an `std::runtime_error` if the file is malformed: the values cannot be parsed or the specified number of columns is greater than the actual number stored in the file.

The use of the class can be seen in the example below:

```cpp
struct person {
    std::string name;
    int age;
};

constexpr std::size_t n_cols = 2;
csv::reader<n_cols> reader{{"dir/people.csv"}};

std::array<std::string, n_cols> header;
std::vector<person> people;
person p;

reader.read_header(header);
while (reader.read_row(p.name, p.age))
    people.emplace_back(p); 
```

## Writing
Writing is enabled using the `csv::writer` class.
It takes the number of columns of the CSV file and a stringifier as its class template parameters.
The default stringifier is `csv::stringifier`, which allows conversion of numbers and enums into `std::string`.
A custom stringifier can also be provided.

The `write_header` method allows writing a header and takes an instance of `std::array` as an argument.
The `write_row` method is used to write the values passed to it directly into rows.
Both methods do not throw any exceptions.

The use of the class can be seen in the example below:

```cpp
struct person {
    std::string name;
    int age;
};

constexpr std::size_t n_cols = 2;
csv::writer<n_cols> writer{{"dir/people.csv"}};

std::array<std::string, n_cols> header{"Name", "Age"};
std::vector<person> people{
        {"Jane",   21},
        {"Max",    47},
        {"George", 7}
};

writer.write_header(header);
for (const auto& p: people)
    writer.write_row(p.name, p.age);
```


