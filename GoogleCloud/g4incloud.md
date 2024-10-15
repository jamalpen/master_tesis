# Instructions to run G4 simulations on the Google Kubernetes Engine (GKC)

These are instructions, largely taylored with the help of AI input, to run Geant4 simulations
on a GKE cluster.  All commands are meant to be run from the Google cloud linux console.
The simulation is based on a G4 container that outputs a file that is later copied to
a Google Storage Bucket, which are visible (after creation) in
the Cloud Storage service of the cloud (it does not show in the
inherent storage section of a GKE cluster).  The files there can later be downloaded manually.

---

### **Step 1: Set Up Google Cloud Project and Enable Kubernetes API**

1. **Create a Google Cloud account** at [https://cloud.google.com](https://cloud.google.com) if you don’t have one.
2. **Create a new project**:
    - In the Google Cloud Console, click the project dropdown and click "New Project."
    - Give it a name and note the **Project ID**.
3. **Enable the Kubernetes Engine API**:
    - In the left-hand menu, go to "APIs & Services" > "Library."
    - Search for **Kubernetes Engine API** and click **Enable**.
4. **Enable Google Cloud Shell**:
    - At the top right of the console, click the **Cloud Shell** icon (a terminal icon). This will open a command-line interface directly within your browser.
5. In addition, I have to make sure to give the appropiate permissions to users with the corresponding credentials

---

### **Step 2: Create a Kubernetes Cluster Using Google Cloud Shell**

1. In the Cloud Shell, authenticate your session (this is automatic for the current project).
2. **Create the Kubernetes cluster** an example on how to do this can be seen here.  Note the usage of "preemptible" machines (check the Annex below for a description):
    ```bash
    gcloud container clusters create my-preemptible-cluster \
    --zone us-central1-a \
    --num-nodes 3 \
    --machine-type e2-standard-4 \
    --preemptible

    ```
    - This command creates a GKE cluster named `my-preemptible-cluster` in the `us-central1-a` zone with 3 nodes of `e2-standard-4` machine type, and these nodes are preemptible.

3. **Configure kubectl to interact with your cluster**:
    ```bash
    gcloud container clusters get-credentials my-preemptible-cluster --zone us-central1-a --project tokyo-receiver-437202-t6
    ```
    This command sets up `kubectl` to communicate with the newly created cluster.  One can get this line from the cluster console by clicking on the three dots next to the new cluster and choosing `connect`.

---

### **Step 3: Create a Google Cloud Storage Bucket for Output Files**

1. **Create the Google Cloud Storage bucket** using Cloud Shell:
    ```bash
    gsutil mb gs://myg4-bucket/
    ```

### **Step 4: Setting up authentication to access Google Cloud Storage (GCS)**

Now, to access GCS from the container, you need to authenticate. You can do this in several ways but we are using a Service Account.
The idea es that one can create a service account with the required permissions to access the GCS bucket and mount its credentials as a secret in your pod. Here are detailed instructions for setting up authentication to access Google Cloud Storage (GCS) from your Kubernetes Job in Google Kubernetes Engine (GKE) using **Service Account**.

1. **Create a Service Account**:
   - Go to the Google Cloud Console.
   - Navigate to **IAM & Admin > Service Accounts**.
   - Click on **+ CREATE SERVICE ACCOUNT**.
   - Provide a name (e.g., `geant4-access`) and description, then click **CREATE**.

2. **Grant Permissions**:
   - On the next page, select the role `Storage Object Admin` or `Storage Object Creator` to allow access to GCS.
   - Click **CONTINUE** and then **DONE**.

3. **Create a Key**:
   - After creating the service account, click on it in the list.
   - Go to the **Keys** tab.
   - Click on **+ ADD KEY** > Create new key > **JSON**.
   - This will download a JSON key file to your computer. Keep it safe.
   - You can now upload this key (the JSON file) to your home area on the Google Cloud.  Just click on the "three dots" menu on the terminal and click upload (note that you can download files from your GC area to your local computer as well). 

4. **Upload the Key to Kubernetes**:
   - Create a Kubernetes secret from the JSON key file:
     ```bash
     kubectl create secret generic gcs-myg4-key --from-file=key.json=/path/to/your-key-file.json
     ```

5. **Check your secret is present**:
    ```bash
    kubectl get secrets
    ```

### **Step 5: Put together a yaml file to run jobs in paralell (GCS)**

Create a yaml file `geant4-job-tobucket.yaml`

```yaml
apiVersion: batch/v1
kind: Job
metadata:
  name: geant4-job-tobucket
spec:
  completions: 6  # Total number of jobs to run
  parallelism: 3   # Limit of parallel jobs running at the same time
  template:
    spec:
      containers:
      - name: geant4-container
        image: jpenafiell/geant4-v10.7.3:latest
        command: ["/bin/bash"]
        args:
        - "-c"
        - |
          # Source Geant4 environment
          source /home/geant4lab/geant4/geant4-v10.7.3-install/share/Geant4-10.7.3/geant4make/geant4make.sh

          # Navigate to the build directory and run the simulation
          cd /home/geant4lab/Geant4_projects/G4_Project/build/
          ./sim -m input.in -t 1

          # Get the pod name to use as a unique identifier for the output file
          POD_NAME=$(hostname)

          # Authenticate with Google Cloud using the service account key
          gcloud auth activate-service-account --key-file=/secret/key.json

          # Copy the simulation results to GCS with a unique name
          gsutil cp /home/geant4lab/Geant4_projects/G4_Project/build/simulation_results.txt gs://myg4-bucket/simulation_results_${POD_NAME}.txt
        volumeMounts:
        - name: gcs-key-volume
          mountPath: /secret
      volumes:
      - name: gcs-key-volume
        secret:
          secretName: gcs-myg4-key
      restartPolicy: Never

```
This YAML file defines a **Kubernetes Job** that runs a Geant4 simulation and uploads the results to Google Cloud Storage (GCS) using a unique name for each job's output.

### Breakdown of the YAML File:

- **apiVersion:** `batch/v1`  
  Specifies that this is a batch job resource.

- **kind:** `Job`  
  The resource type is a Kubernetes Job.

- **metadata:**  
  - **name:** `geant4-job-tobucket`  
    The name of the job is `geant4-job-tobucket`.

- **spec:**  
  Defines the specifications of the job:
  - **completions:** `6`  
    The job will execute 6 times (6 pods will run in total).
  - **parallelism:** `3`  
    A maximum of 3 pods will run in parallel at any time.

- **template:**  
  - **spec:**  
    Defines the specifications for the individual job pods:
    - **containers:**  
      Defines the container used by the job:
      - **name:** `geant4-container`  
        Name of the container running inside the pod.
      - **image:** `jpenafiell/geant4-v10.7.3:latest`  
        The Docker image to be used is `jpenafiell/geant4-v10.7.3:latest`, which contains the Geant4 simulation environment.
      - **command:** `["/bin/bash"]`  
        The command to be run in the container.
      - **args:**  
        A bash script is passed as arguments to run the simulation and copy the output to Google Cloud Storage:
        1. **Source Geant4 environment:** It sources the Geant4 environment using a script.
        2. **Navigate to the build directory:** Changes the working directory to the build directory where the simulation executable is located.
        3. **Run the simulation:** Executes the simulation using the `./sim` command with an input file (`input.in`) and a single thread (`-t 1`).
        4. **Get pod name:** Fetches the pod's hostname (which is unique per pod) to use as a unique identifier for the output file.
        5. **Authenticate with Google Cloud:** Authenticates using a service account key from a secret volume.
        6. **Copy results to GCS:** Uses `gsutil cp` to upload the simulation result file to the Google Cloud Storage bucket with a unique name based on the pod's hostname.
        
    - **volumeMounts:**  
      Mounts a volume to provide the service account key:
      - **name:** `gcs-key-volume`  
        The name of the volume is `gcs-key-volume`.
      - **mountPath:** `/secret`  
        The volume is mounted at `/secret` inside the container, which is where the key for Google Cloud is stored.
    
    - **volumes:**  
      Defines the volume for the secret:
      - **name:** `gcs-key-volume`  
        The volume name is `gcs-key-volume`.
      - **secret:**  
        The volume is a Kubernetes secret that contains the Google Cloud service account key.
      - **secretName:** `gcs-myg4-key`  
        The secret used is called `gcs-myg4-key`.

    - **restartPolicy:** `Never`  
      The pods will not restart if they fail, as the policy is set to `Never`.

### Functionality:

1. **Parallel Execution:** The job will execute 6 times, with 3 instances running in parallel.
2. **Geant4 Simulation:** Each instance runs a Geant4 simulation.
3. **Unique Output:** The simulation result is saved with a unique name based on the pod's hostname.
4. **Google Cloud Integration:** The results are uploaded to a Google Cloud Storage bucket using a service account key stored in a Kubernetes secret.

---

### **Step 6: Run the yaml file**
```bash
kubectl apply -f geant4-job-tobucket.yaml
```

The results should get copied to the bucket.  You can download the results directly from the web interface.

You can check the status of jobs or pods using

```bash
kubectl get jobs
kubectl get pods
kubectl logs <pod id>
```
or just search for more alternatives.

### **Step 7: Erase everything**

Make sure you erase the bucket and the cluster so everything gets wiped out and we don't get charged in periods of silence.



### Annex

A **preemptible** virtual machine (VM) in Google Cloud is a short-lived, cost-effective instance that can be shut down by Google Cloud at any time, usually when resources are needed elsewhere. Preemptible VMs are generally much cheaper than regular VMs but come with certain limitations.

### Key Characteristics of Preemptible VMs:
1. **Lower Cost**: Preemptible VMs can be up to 80% cheaper than regular instances, making them ideal for workloads that can tolerate interruptions, such as batch processing, distributed computation, and simulation tasks.
   
2. **Short Lifespan**: Preemptible instances have a maximum lifetime of 24 hours. After this period, they are automatically terminated.

3. **Can be Interrupted**: Google Cloud can terminate (or "preempt") these instances if it needs to free up resources for other, higher-priority workloads. This termination can happen without prior notice.

4. **No Guarantees of Availability**: There is no guarantee that preemptible VMs will always be available when you try to create them, as it depends on the current capacity of the Google Cloud data centers.

5. **Use Cases**: Preemptible VMs are commonly used for:
   - Batch jobs
   - Big data processing
   - CI/CD pipelines
   - Machine learning model training
   - Simulations and rendering jobs, such as scientific computing (e.g., physics simulations)

### Example Use Cases:
For your case, running multiple instances of your simulation job in Kubernetes (GKE) using preemptible nodes can significantly reduce costs if the jobs can handle the risk of being interrupted and restarted.

However, preemptible nodes may not be the best fit if the workload requires guaranteed uptime or immediate completion without the risk of interruptions.