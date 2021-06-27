package finalproject2;

import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Scanner;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import java.io.FileInputStream;
import java.io.Reader;
import java.util.ArrayList;

public class Finalproject2 {
    
    public static void main(String [] args) throws IOException {
        while (true) {
            System.out.println("What would you like to monitor?");
            System.out.println("Enter 1 to monitor Animals");
            System.out.println("Enter 2 to monitor Habitats");
            System.out.println("Enter 3 to Exit");
            int userInput = 0;
            int write = 0;
            Scanner sc = new Scanner(System.in);
            userInput = sc.nextInt();
            String animalName;
            String habitatName;
            
            if (userInput == 1) {
                System.out.println("List of Animals");
                Scanner s = new Scanner(new File("//Users//rickydiaz//NetBeansProjects//finalproject2//src//finalproject2//animals.txt"));
                ArrayList<String> list = new ArrayList<>();
                while (s.hasNextLine()) {
                    list.add(s.nextLine());
                }
                s.close();
                
                for (String line : list) {
                    if (line.toLowerCase().contains("Details on".toLowerCase())) {
                        write = write + 1;
                        System.out.println(line);
                    }
                    }
                
                System.out.println("Enter name of animal you would like to monitor:");
                animalName = sc.next();
                for (String zoo : list.subList(write, list.size())) {
                    if (zoo.toLowerCase().contains(animalName.toLowerCase())) {
                        write = list.indexOf(zoo);
                        for (int i = write; i < write + 5; i++) {
                            if (list.get(i).contains("*****")) {
                                JOptionPane.showMessageDialog(new JFrame(), list.get(i), "ALERT!!!", JOptionPane.ERROR_MESSAGE);
                                break;
                            }
                            else {
                                System.out.println(list.get(i));
                            }
                        }
                    }
                }
            }
            else if (userInput == 2) {
                System.out.println("List of Habitats");
                Scanner s = new Scanner(new File("//Users//rickydiaz//NetBeansProjects//finalproject2//src//finalproject2//habitats.txt"));
                ArrayList<String> list = new ArrayList<>();
                while (s.hasNextLine()) {
                    list.add(s.nextLine());
                }
                s.close();
                
                for (String line : list) {
                    if (line.toLowerCase().contains("Details on".toLowerCase())) {
                        write = write + 1;
                        System.out.println(line);
                    }
                }
                System.out.println("Enter the name of a habitat you would like to monitor:");
                habitatName = sc.next();
                for (String zoo : list.subList(write, list.size())) {
                    if (zoo.toLowerCase().contains(habitatName.toLowerCase())) {
                        write = list.indexOf(zoo);
                        for (int i = write; i < write + 4; i++) {
                            if (list.get(i).contains("*****")) {
                                JOptionPane.showMessageDialog(new JFrame(), list.get(i), "ALERT!!!", JOptionPane.ERROR_MESSAGE);
                                break;
                            }
                            else {
                                System.out.println(list.get(i));
                            }
                        }
                    }
                }
            }
            else if (userInput == 3) {
                sc.close();
                System.exit(0);
            }
        }
    }
    
    
}

