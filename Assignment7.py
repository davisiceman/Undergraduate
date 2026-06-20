import re
import pandas as pd
from collections import Counter

def extract_emails_and_urls(file_path):
    try:
        with open(file_path, 'rb') as f:
            data = f.read()
    except Exception as e:
        print(f"Error reading file: {e}")
        return
    
    # Regular expressions for extracting emails and URLs
    ePatt = re.compile(b'[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}')
    uPatt = re.compile(b'\w+:\/\/[\w@][\w.:@]+\/?[\w.\.?=%&=\-@$,]*')
    
    emails = ePatt.findall(data)
    urls = uPatt.findall(data)
    
    # Decode extracted data
    decoded_emails = [email.decode(errors='ignore') for email in emails]
    decoded_urls = [url.decode(errors='ignore') for url in urls]
    
    # Count occurrences
    email_counts = Counter(decoded_emails)
    url_counts = Counter(decoded_urls)
    
    # Convert results to DataFrames
    email_df = pd.DataFrame(email_counts.items(), columns=["Email", "Occurrences"])
    url_df = pd.DataFrame(url_counts.items(), columns=["URL", "Occurrences"])
    
    return email_df, url_df

if __name__ == "__main__":
    file_path = "test.bin"  # Update this path if needed
    email_df, url_df = extract_emails_and_urls(file_path)
    
    if email_df is not None:
        print("Extracted Emails:")
        print(email_df)
    
    if url_df is not None:
        print("Extracted URLs:")
        print(url_df)