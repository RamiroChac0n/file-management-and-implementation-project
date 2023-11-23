CREATE TABLE account (
    id_account INT NOT NULL,
    password VARCHAR(255) NOT NULL,
    funds DOUBLE NOT NULL,
    id_bank INT NOT NULL,
    id_type INT NOT NULL,
    id_client INT NOT NULL,
    PRIMARY KEY (id_client),
    FOREIGN KEY (id_bank) REFERENCES bank(id_bank),
    FOREIGN KEY (id_type) REFERENCES type(id_type),
    FOREIGN KEY (id_client) REFERENCES client(id_client)
);