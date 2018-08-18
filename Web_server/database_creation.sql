CREATE DATABASE integrator_project_2 

CREATE TABLE `integrator_project_2`.`received_data` ( `index` INT NOT NULL AUTO_INCREMENT , `team` VARCHAR(10) NOT NULL , `local` VARCHAR(10) NOT NULL , `volume` INT NOT NULL , `color` VARCHAR NOT NULL , `date` DATETIME NOT NULL , PRIMARY KEY (`index`(2048))) ENGINE = InnoDB;