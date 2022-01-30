

public class csCannon : MonoBehaviour 
{
	float power = 900.0f;
	Vector3 velocity;

	void Start() 
	{
		velocity = transform.forward * power;

		GetComponent<Rigidbody>().AddForce( velocity );
		StartCoroutine ("DeleteCannon");
	}

	IEnumerator DeleteCannon() {
		yield return new WaitForSeconds (0.5f);
		Destroy(this.gameObject);
	}

}
