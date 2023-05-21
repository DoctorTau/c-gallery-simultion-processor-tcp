int main(){
// Create visitors
    for (int i = 0; i < number_of_visitors; i++) {
        int pid = fork();
        if (pid == 0) {
            // Visitor
            bool visited_pictures[NUMBER_OF_PICTURES];
            int time_to_stay = getRandomNumber(1, 5);

            // Wait for the gallery to be free
            sem_wait(gallery_sem_pointer);
            for (;;) {
                int picture_number = getRandomNumber(0, NUMBER_OF_PICTURES - 1);
                // Wait for the picture to be free
                sem_wait(picture_sems_pointers[picture_number]);

                // Look at the picture
                sleep(time_to_stay);

                // Leave the picture
                sem_post(picture_sems_pointers[picture_number]);

                // Mark the picture as visited
                visited_pictures[picture_number] = true;

                // If all pictures have been visited, leave the gallery
                if (isAllTrue(visited_pictures)) {
                    break;
                }
            }
            printGalleryInfo();
            // Leave the gallery
            sem_post(gallery_sem_pointer);

            return 0;
        }
    }
}