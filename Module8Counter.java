public class Module8Counter {
    private static final int FIRST_COUNT = 0;
    private static final int LAST_COUNT = 20;

    public static void main(String[] args) {
        // The first thread prints each value from 0 through 20.
        Thread countUpThread = new Thread(() -> {
            System.out.print("Count up:   ");
            for (int count = FIRST_COUNT; count <= LAST_COUNT; count++) {
                System.out.print(count + (count == LAST_COUNT ? "\n" : " "));
            }
        });

        // The second thread prints the same values in reverse order.
        Thread countDownThread = new Thread(() -> {
            System.out.print("Count down: ");
            for (int count = LAST_COUNT; count >= FIRST_COUNT; count--) {
                System.out.print(count + (count == FIRST_COUNT ? "\n" : " "));
            }
        });

        try {
            countUpThread.start();
            // Wait for the first thread to finish before starting the second.
            countUpThread.join();

            countDownThread.start();
            // Wait for the countdown before the program finishes.
            countDownThread.join();
        } catch (InterruptedException error) {
            // Restore the interrupt status and report that the wait ended early.
            Thread.currentThread().interrupt();
            System.err.println(
                    "The program was interrupted while waiting for a thread.");
        }
    }
}
