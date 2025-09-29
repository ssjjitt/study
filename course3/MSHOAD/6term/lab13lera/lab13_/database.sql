use lab13;

CREATE TABLE dim_date (
    date_id INT PRIMARY KEY,
    full_date DATE,
    day INT,
    month INT,
    quarter INT,
    year INT,
    month_name VARCHAR(15)
);

CREATE TABLE dim_route (
    route_id INT PRIMARY KEY,
    route_name VARCHAR(100),
    origin_city VARCHAR(50),
    destination_city VARCHAR(50),
    region VARCHAR(50)
);

CREATE TABLE dim_client (
    client_id INT PRIMARY KEY,
    client_name VARCHAR(100),
    client_type VARCHAR(20), -- "Individual" / "Company"
    industry VARCHAR(50)
);


CREATE TABLE dim_transport (
    transport_id INT PRIMARY KEY,
    transport_type VARCHAR(30),
    model VARCHAR(50),
    capacity_tons DECIMAL(5,2)
);


CREATE TABLE dim_driver (
    driver_id INT PRIMARY KEY,
    driver_name VARCHAR(100),
    experience_years INT,
    license_category VARCHAR(10)
);

CREATE TABLE fact_shipments (
    shipment_id INT PRIMARY KEY,
    date_id INT,
    route_id INT,
    client_id INT,
    transport_id INT,
    cost DECIMAL(10,2),
    distance_km INT,
    travel_time_hours DECIMAL(5,2),
    
    FOREIGN KEY (date_id) REFERENCES dim_date(date_id),
    FOREIGN KEY (route_id) REFERENCES dim_route(route_id),
    FOREIGN KEY (client_id) REFERENCES dim_client(client_id),
    FOREIGN KEY (transport_id) REFERENCES dim_transport(transport_id)
);

INSERT INTO dim_date (date_id, full_date, day, month, quarter, year, month_name) VALUES
(1, '2024-01-15', 15, 1, 1, 2024, 'January'),
(2, '2024-02-20', 20, 2, 1, 2024, 'February'),
(3, '2024-03-10', 10, 3, 1, 2024, 'March'),
(4, '2024-04-05', 5, 4, 2, 2024, 'April'),
(5, '2024-05-25', 25, 5, 2, 2024, 'May'),
(6, '2024-06-18', 18, 6, 2, 2024, 'June'),
(7, '2024-07-02', 2, 7, 3, 2024, 'July'),
(8, '2024-08-12', 12, 8, 3, 2024, 'August'),
(9, '2024-09-30', 30, 9, 3, 2024, 'September'),
(10, '2024-10-07', 7, 10, 4, 2024, 'October');

INSERT INTO dim_route (route_id, route_name, origin_city, destination_city, region) VALUES
(1, 'Route A1', 'New York', 'Boston', 'Northeast'),
(2, 'Route B2', 'Chicago', 'Detroit', 'Midwest'),
(3, 'Route C3', 'Dallas', 'Houston', 'South'),
(4, 'Route D4', 'San Francisco', 'Los Angeles', 'West'),
(5, 'Route E5', 'Seattle', 'Portland', 'Northwest');

INSERT INTO dim_client (client_id, client_name, client_type, industry) VALUES
(1, 'Acme Corp', 'Company', 'Manufacturing'),
(2, 'Global Logistics', 'Company', 'Transport'),
(3, 'John Doe', 'Individual', 'Private'),
(4, 'Eco Delivery', 'Company', 'E-commerce'),
(5, 'Jane Smith', 'Individual', 'Private');

INSERT INTO dim_transport (transport_id, transport_type, model, capacity_tons) VALUES
(1, 'Truck', 'Volvo FH', 20.0),
(2, 'Van', 'Mercedes Sprinter', 3.5),
(3, 'Truck', 'Scania R450', 25.0),
(4, 'Trailer', 'MAN TGX', 30.0),
(5, 'Van', 'Ford Transit', 4.0);

INSERT INTO dim_driver (driver_id, driver_name, experience_years, license_category) VALUES
(1, 'Mike Johnson', 5, 'C'),
(2, 'Anna Smith', 7, 'CE'),
(3, 'David Lee', 3, 'C'),
(4, 'Emily White', 10, 'CE'),
(5, 'Chris Brown', 6, 'C');

INSERT INTO fact_shipments (shipment_id, date_id, route_id, client_id, transport_id, cost, distance_km, travel_time_hours) VALUES
(1, 1, 1, 1, 1, 1500.00, 320, 5.5),
(2, 2, 2, 2, 2, 800.00, 200, 4.0),
(3, 3, 3, 3, 3, 500.00, 150, 3.0),
(4, 4, 4, 4, 4, 2200.00, 560, 8.5),
(5, 5, 5, 5, 5, 650.00, 180, 3.5),
(6, 6, 1, 1, 2, 1400.00, 310, 5.0),
(7, 7, 2, 3, 3, 900.00, 250, 4.5),
(8, 8, 3, 2, 1, 1300.00, 300, 6.0),
(9, 9, 4, 5, 2, 1600.00, 400, 6.5),
(10, 10, 5, 4, 4, 2100.00, 500, 7.5),
(11, 3, 3, 1, 1, 700.00, 220, 3.8),
(12, 4, 2, 2, 2, 1200.00, 280, 4.9),
(13, 5, 1, 3, 3, 1100.00, 260, 4.2);
